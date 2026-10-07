/* 
 * File:   alarms.h
 * Author: ferre
 *
 * Created on 6 de Outubro de 2026, 19:01
 */

#ifndef ALARMS_H
#define	ALARMS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "stdint.h"
    
extern uint8_t ALAH;
extern uint8_t ALAM;
extern uint8_t ALAS;
extern unsigned char ALAT;
extern uint8_t ALAL;

unsigned char alarm(unsigned char c, uint8_t bright);


#ifdef	__cplusplus
}
#endif

#endif	/* ALARMS_H */

