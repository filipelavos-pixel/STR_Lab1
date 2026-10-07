#include "../mcc_generated_files/memory.h"
#include "../Clock/clock.h"
#include "eeprom.h"
#include "stdint.h"

unsigned char temperature_max;
unsigned char temperature_min;
uint8_t bright_max;
uint8_t bright_min;
char eeprom_start = 0;

void eeprom_record(uint16_t EEAddr, unsigned char c, uint8_t bright) {
    
    if (eeprom_start == 0){
        eeprom_start = 1;
        temperature_max = c;
        temperature_min = c;
        bright_max = bright;
        bright_min = bright;
        for (int i=0; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, clk_h);
        }
        for (int i=1; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, clk_m);
        }
        for (int i=2; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, clk_s);
        }
        for (int i=3; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, c);
        }
        for (int i=4; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, bright);
        }
    }else{
        if (c > temperature_max){
            temperature_max = c;
            DATAEE_WriteByte(EEAddr, clk_h);
            DATAEE_WriteByte(EEAddr + 1, clk_m);
            DATAEE_WriteByte(EEAddr + 2, clk_s);
            DATAEE_WriteByte(EEAddr + 3, c);
            DATAEE_WriteByte(EEAddr + 4, bright);
        }
        if (c < temperature_min){
            temperature_min = c;
            DATAEE_WriteByte(EEAddr + 5, clk_h);
            DATAEE_WriteByte(EEAddr + 6, clk_m);
            DATAEE_WriteByte(EEAddr + 7, clk_s);
            DATAEE_WriteByte(EEAddr + 8, c);
            DATAEE_WriteByte(EEAddr + 9, bright);
        }
        if (bright > bright_max){
            bright_max = bright;
            DATAEE_WriteByte(EEAddr + 10, clk_h);
            DATAEE_WriteByte(EEAddr + 11, clk_m);
            DATAEE_WriteByte(EEAddr + 12, clk_s);
            DATAEE_WriteByte(EEAddr + 13, c);
            DATAEE_WriteByte(EEAddr + 14, bright);
        }
        if (bright < bright_min){
            bright_min = bright;
            DATAEE_WriteByte(EEAddr + 15, clk_h);
            DATAEE_WriteByte(EEAddr + 16, clk_m);
            DATAEE_WriteByte(EEAddr + 17, clk_s);
            DATAEE_WriteByte(EEAddr + 18, c);
            DATAEE_WriteByte(EEAddr + 19, bright);
        }
    }

}
