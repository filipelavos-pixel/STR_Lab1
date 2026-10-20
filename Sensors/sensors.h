/* 
 * File:   sensors.h
 * Author: ferre
 *
 * Created on 5 de Outubro de 2026, 15:36
 */

#ifndef SENSORS_H
#define	SENSORS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "stdint.h"
#include "stdbool.h"

void TC74_standby(bool on);
unsigned char readTC74 (void);
uint8_t brightness(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SENSORS_H */

