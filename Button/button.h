/* 
 * File:   button.h
 * Author: ferre
 *
 * Created on 14 de Outubro de 2026, 0:36
 */

#ifndef BUTTON_H
#define	BUTTON_H


#ifdef	__cplusplus
extern "C" {
#endif

    extern uint8_t mode;
    extern uint8_t mode_count;
    extern uint8_t presentation_counter;
    extern bool alarm_clock;
    extern bool alarm_c;
    extern bool alarm_bright;
    
    void button_control(uint16_t EEAddr, unsigned char c, uint8_t bright);


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */

