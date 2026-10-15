/* 
 * File:   parameters_block.h
 * Author: ferre
 *
 * Created on October 12, 2026, 8:58 PM
 */

#ifndef PARAMETERS_BLOCK_H
#define	PARAMETERS_BLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"

    // Parameters block at the begin of the EEPROM (MW ... checksum)
#define PARAMS_ADDR 0x7000
#define MAGIC_WORD  0xA5

    typedef struct {
        uint8_t MW;      
        uint8_t PMON;      
        uint8_t TALA;    
        uint8_t ALAF;  
        uint8_t ALAH;  
        uint8_t ALAM;   
        uint8_t ALAS;  
        uint8_t ALAT;
        uint8_t ALAL;
        uint8_t CLKH;
        uint8_t CLKM;
        uint8_t checksum;       
    } Config_Parameters;

    
    extern Config_Parameters parameters;
    extern volatile bool param_change;

    void DefaultParameters(void);
    uint8_t params_checksum(Config_Parameters *p);
    void params_save(void);
    bool params_load(void);




#ifdef	__cplusplus
}
#endif

#endif	/* PARAMETERS_BLOCK_H */

