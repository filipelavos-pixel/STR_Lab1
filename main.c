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


#define EEAddr    0x7000



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

    // Initial State for Alarm Sinalization: OFF
    PWM6_LoadDutyValue(0);
    TMR2_StopTimer();

    DefaultParameters();


    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    OpenI2C();
    //I2C_SCL = 1;
    //I2C_SDA = 1;
    //WPUC3 = 1;
    //WPUC4 = 1;
    LCDinit();
    LCDcmd(0x0C);       // display on, cursor off (LCDinit leaves it on)
    //clock initialized, and PWM
    TMR1_SetInterruptHandler(clock_isr);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    //Readings for inicial record
    tmp = readTC74();
    bright = brightness();
    eeprom_record(EEAddr, tmp, bright);
    
    
    while (1)
    {   
        //Button user interactions and its effects
        button_control(EEAddr, tmp, bright);
        // After each 1 second, everything down runs
        if (tick_1s) { 
            tick_1s = false; 
            LED_D5_Toggle();
            
            pmon++;
            
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
                // The sinalization has to be stopped
                PWM6_LoadDutyValue(0);
                TMR2_StopTimer();
                enabled_D2 = false;
                pwm_count = 0;
            }

            // PWM sinalization is stopped when the intended duration is achieved
            if(enabled_D2 && pwm_count >= parameters.TALA) {
                PWM6_LoadDutyValue(0);
                TMR2_StopTimer();
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
            //Reading temperature and brightness every PMON seconds
            if (pmon >= parameters.PMON){
                tmp = readTC74();
                bright = brightness();
                eeprom_record(EEAddr, tmp, bright);
                pmon = 0;
                
            }
        }
            
    }
}

/**
 End of File
*/