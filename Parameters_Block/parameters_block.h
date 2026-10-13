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
    
    void DefaultParameters(void);




#ifdef	__cplusplus
}
#endif

#endif	/* PARAMETERS_BLOCK_H */

