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

void normal_interface(unsigned char c, uint8_t bright, bool alarm_clock, bool alarm_c, bool alarm_bright);
void switch_interface();
void configuration_interface(uint8_t position, unsigned char c, uint8_t bright, bool current);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERFACE_H */

