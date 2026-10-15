/* 
 * File:   interface.h
 * Author: ferre
 *
 * Created on October 13, 2026, 1:02 AM
 */

#ifndef INTERFACE_H
#define	INTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif

void normal_interface(unsigned char tmp, uint8_t bright, bool alarm_clock, bool alarm_tmp, bool alarm_bright);
void switch_interface();
void configuration_interface(uint8_t position, unsigned char tmp, uint8_t bright, bool current);
void LCD_max_min(uint16_t EEAddr, uint8_t presentation_counter);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERFACE_H */

