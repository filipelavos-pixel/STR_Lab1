/* 
 * File:   usart.h
 * Author: ferre
 *
 * Created on October 21, 2026, 10:51 AM
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "stdint.h"
#include "stdbool.h"

void usart_init(void);
void usart_task(void);
void read_usart(void);
void write_usart(void);
bool usart_tx_busy(void);


#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

