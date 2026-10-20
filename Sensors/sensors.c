
#include "../I2C/i2c.h"
#include "../Clock/clock.h"
#include "sensors.h"
#include "../mcc_generated_files/adcc.h"
#include "stdint.h"
#include "../Parameters_Block/parameters_block.h"

// Puts the TC74 in standby (SHDN = 1) or in normal mode (SHDN = 0)
void TC74_standby(bool on)
{
	IdleI2C();
	StartI2C(); IdleI2C();
	WriteI2C(0x9a | 0x00); IdleI2C();
	WriteI2C(0x01); IdleI2C();
	WriteI2C(on ? 0x80 : 0x00); IdleI2C();
	StopI2C();
}

// Reads temperature from sensor
unsigned char readTC74 (void)
{
	unsigned char value;
	uint16_t tries = 0;

	TC74_standby(false);   // wake up (no effect if already awake)
do{
	IdleI2C();
	StartI2C(); IdleI2C();
    
	WriteI2C(0x9a | 0x00); IdleI2C();
	WriteI2C(0x01); IdleI2C();
	RestartI2C(); IdleI2C();
	WriteI2C(0x9a | 0x01); IdleI2C();
	value = ReadI2C(); IdleI2C();
	NotAckI2C(); IdleI2C();
	StopI2C();
} while (!(value & 0x40) && ++tries < 500);   // timeout (~0.5 s) if DATA_RDY never sets

	IdleI2C();
	StartI2C(); IdleI2C();
	WriteI2C(0x9a | 0x00); IdleI2C();
	WriteI2C(0x00); IdleI2C();
	RestartI2C(); IdleI2C();
	WriteI2C(0x9a | 0x01); IdleI2C();
	value = ReadI2C(); IdleI2C();
	NotAckI2C(); IdleI2C();
	StopI2C();

	// Standby between readings, except with PMON = 1 (read every second)
	if (parameters.PMON != 1) {
		TC74_standby(true);
	}

	return value;
}

//Reads and calculates brightness correctly from potentiometer
uint8_t brightness(void){
    
    uint16_t adcResult = ADCC_GetSingleConversion(POT_CHANNEL);
    
    adcResult = adcResult/128;
    return (uint8_t) adcResult;
}