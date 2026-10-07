/*
 * Test: ADC + potentiometer + LCD
 *
 * Expected behaviour:
 * - ADC raw value: approximately 0..1023
 * - brightness level: 0..7
 *
 * Status:
 * VERIFIED ON BOARD - 07/10/2026
 * 
 * To use - copy this script to main.c
 */

/*

#include "mcc_generated_files/mcc.h"
#include "I2C/i2c.h"
#include "LCD/lcd.h"
#include "Sensors/sensors.h"

#include <stdio.h>
#include <stdint.h>

void main(void)
{
    uint16_t adcValue;
    uint8_t level;
    char buf[17];

    SYSTEM_Initialize();

    OpenI2C();
    LCDinit();

    while (1)
    {
        adcValue = ADCC_GetSingleConversion(POT_CHANNEL);
        level = brightness();

        LCDcmd(0x80);
        while (LCDbusy());

        sprintf(buf, "ADC: %4u", adcValue);
        LCDstr(buf);

        LCDcmd(0xC0);
        while (LCDbusy());

        sprintf(buf, "Level: %u", level);
        LCDstr(buf);

        __delay_ms(200);
    }
}

*/