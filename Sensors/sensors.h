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

unsigned char readTC74 (void);
uint16_t brightness(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SENSORS_H */

