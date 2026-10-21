/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F18875
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "I2C/i2c.h"
#include "LCD/lcd.h"
#include "Clock/clock.h"
#include "Sensors/sensors.h"
#include "EEPROM/eeprom.h"
#include "Alarms/alarms.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "Parameters_Block/parameters_block.h"
#include "Interface/interface.h"
#include "Button/button.h"


// Max/min records go right after the parameters block
#define EEAddr    (PARAMS_ADDR + sizeof(Config_Parameters))



/*
                         Main application
 */
    

void main(void)
{    
    unsigned char tmp;
    uint8_t bright;
    unsigned char pmon = 0; //Counter for PMON duration
    unsigned char pwm_count = 0; //Counter for PWM duration
    bool enabled_D2 = false;
    
    // initialize the device
    SYSTEM_Initialize();
    
    IOCBPbits.IOCBP4 = 1;   // S1 released (rising edge)
    IOCBNbits.IOCBN4 = 1;   // S1 pressed (falling edge)
    IOCCPbits.IOCCP5 = 1;   // S2 released
    IOCCNbits.IOCCN5 = 1;   // S2 pressed
    IOCBFbits.IOCBF4 = 0;   //change to 1 when button is changed
    IOCCFbits.IOCCF5 = 0;   //change to 1 when button is changed
    
    // Initial State for Alarm Signalization: OFF
    PWM6_LoadDutyValue(0);
    TMR2_StartTimer();

    // Restore saved parameters, or use (and save) the defaults if MW/checksum fail
    if (!params_load()) {
        DefaultParameters();
        params_save();
    }

    OpenI2C();

    LCDinit();
    LCDcmd(0x0C);       // display on, cursor off (LCDinit leaves it on)
    //clock initialized, and PWM
    TMR1_SetInterruptHandler(clock_isr);
    TMR4_SetInterruptHandler(debounce_isr);
     // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
   
    //if eeprom does not have values of parameters stored, record values for the first time
    if (DATAEE_ReadByte(EEAddr) == 0xFF && DATAEE_ReadByte(EEAddr + 1) == 0xFF) {
        tmp = readTC74();
        bright = brightness();
        eeprom_start = 0;
        eeprom_record(EEAddr, tmp, bright);
    }
    
    while (1)
    {   
        // A button changed: (re)start the debounce
        if (IOCBFbits.IOCBF4 || IOCCFbits.IOCCF5) {
            IOCBFbits.IOCBF4 = 0;
            IOCCFbits.IOCCF5 = 0;
            debounce_start();
        }
        //Button user interactions and its effects (only read when stable)
        if (!debouncing) {
            button_control(EEAddr, tmp, bright);
        }
        // Save the parameters block when something changed
        if (param_change) {
            param_change = false;
            params_save();
        }
        // After each 1 second, everything down runs
        if (tick_1s) { 
            tick_1s = false; 
            LED_D5_Toggle();
            
            
            //all real time conditions(see button.c properly)
            if (mode == 1){
                mode_count++;
            }
            if (mode == 3){
                presentation_counter++;
            }

            // Increments the time passed on an active PWM signal for the D2 LED
            if (enabled_D2) {
                pwm_count++;
            }

            // Detecting Alarm conditions
            if (parameters.ALAF == 1) {
                // alarm() sets the C/T/L flags, returns true on a new alarm
                if (alarm(tmp, bright)) {
                    // Start the PWM signal only if it's OFF
                    if (!enabled_D2) {
                        pwm_count = 0;
                        PWM6_LoadDutyValue(800);
                        TMR2_StartTimer();
                        enabled_D2 = true;
                    }
                }

            } else {
                // Here, alarms are deactivated --> ALAF = 0
                // The signalization has to be stopped
                if (enabled_D2) {
                    PWM6_LoadDutyValue(0);
                    PIR4bits.TMR2IF = 0;
                    while (!TMR2_HasOverflowOccured());   // wait for the period end so duty 0 is applied before SLEEP
                }
                enabled_D2 = false;
                pwm_count = 0;
            }

            // PWM signalization is stopped when the intended duration is achieved
            if(enabled_D2 && pwm_count >= parameters.TALA) {
                PWM6_LoadDutyValue(0);
                PIR4bits.TMR2IF = 0;
                while (!TMR2_HasOverflowOccured());   // wait for the period end so duty 0 is applied before SLEEP
                enabled_D2 = false;
                pwm_count = 0;
            }

            //Light up two LEDS for reach threshold limits
            if (tmp > parameters.ALAT){
                LED_D4_SetHigh();
            }
            else{
                LED_D4_SetLow();
            }
            if (bright < parameters.ALAL){
                LED_D3_SetHigh();
            }
            else{
                LED_D3_SetLow();
            }
            
            //Reading temperature and brightness every PMON seconds (should be disabled when PMON is zero)
            // Periodic monitoring is disabled when PMON is zero.
            if (parameters.PMON > 0) {
                pmon++;

                // Wake the TC74 one tick before the reading, so it is ready
                if (pmon == parameters.PMON - 1) {
                    TC74_standby(false);
                }

                if (pmon >= parameters.PMON) {
                    tmp = readTC74();
                    bright = brightness();
                    eeprom_record(EEAddr, tmp, bright);
                    pmon = 0;
                }
            }
            else {
                pmon = 0;
            }
        }
        
        
        INTERRUPT_GlobalInterruptDisable(); //stops the jumps caused by the Timer 1 but the flag still changes so the clock will be updated when this gets enabled again
        // No sleep while debouncing: TMR4 (FOSC/4) stops in sleep
        if (!tick_1s && !param_change && !enabled_D2 && !debouncing) {
            PIE0bits.IOCIE = 1; //turn on the wakeup with the buttons
            SLEEP();
            NOP(); //after sleep continues here and the NOP was recommended in the datasheet
            PIE0bits.IOCIE = 0; //turn off the wakeup with the buttons
        }
        // The IOC flags are only cleared at the top of the loop, where the debounce starts
        INTERRUPT_GlobalInterruptEnable();
    }
}

/**
 End of File
*/