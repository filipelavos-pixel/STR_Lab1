/* 
 * File:   eeprom.h
 * Author: ferre
 *
 * Created on October 6, 2026, 2:30 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "stdint.h"

extern unsigned char temperature_max;
extern unsigned char temperature_min;
extern uint8_t bright_max;
extern uint8_t bright_min;
extern uint8_t eeprom_start;


void eeprom_record(uint16_t EEadr, unsigned char tmp, uint8_t bright);
void eeprom_read_records(uint16_t EEAddr, char buf1[17], char buf2[17], char buf3[17], char buf4[17]);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

