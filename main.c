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


#define EEAddr    0x7000



/*
                         Main application
 */
    

void main(void)
{    
    unsigned char c;
    uint8_t bright;
    unsigned char pmon = 0;
    unsigned char pwm_count = 0;
    bool eeprom_first = false;

    // initialize the device
    SYSTEM_Initialize();
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

    TMR1_SetInterruptHandler(clock_isr);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    TMR2_Initialize();
    PWM6_Initialize();
    
    while (1)
    {
        // Add your application code
        if (tick_1s) { 
            tick_1s = false; 
            LED_D5_Toggle();
            
            pmon++;
            
            if (eeprom_first){
                if (parameters.ALAF == 1){
                    unsigned char alarm_type = alarm(c, bright);
                    if (alarm_type != 0){
                        TMR2_StartTimer();
                        PWM6_LoadDutyValue(800);
                        pwm_count++;
                        if (pwm_count >= parameters.TALA){
                            PWM6_LoadDutyValue(0);
                            TMR2_StopTimer();
                            pwm_count = 0;
                        }
                    }
                    else {
                        pwm_count = 0;
                    }
                }
                if (c > parameters.ALAT){
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
            }
            if (pmon >= parameters.PMON){
                c = readTC74();
                bright = brightness();
                eeprom_record(EEAddr, c, bright);
                eeprom_first = true;
                pmon = 0;
                
            }
            normal_interface(c, bright);
        }
            
    }
}

/**
 End of File
*/