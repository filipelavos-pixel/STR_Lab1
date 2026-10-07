/* 
 * File:   clock.h
 * Author: ferre
 *
 * Created on 5 de Outubro de 2026, 15:35
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "stdint.h"
#include "stdbool.h"


extern volatile uint8_t clk_h;
extern volatile uint8_t clk_m;
extern volatile uint8_t clk_s;
extern volatile bool tick_1s;

void clock_isr(void);


#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

