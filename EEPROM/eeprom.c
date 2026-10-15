#include "../mcc_generated_files/memory.h"
#include "../Clock/clock.h"
#include "eeprom.h"
#include "stdint.h"
#include "../Parameters_Block/parameters_block.h"
#include "../mcc_generated_files/mcc.h"

unsigned char temperature_max;
unsigned char temperature_min;
uint8_t bright_max;
uint8_t bright_min;
uint8_t eeprom_start = 0;

//Record values of temperature and brightness in memory
void eeprom_record(uint16_t EEAddr, unsigned char tmp, uint8_t bright) {
    
    if (eeprom_start == 0){
        eeprom_start = 1;
        temperature_max = tmp;
        temperature_min = tmp;
        bright_max = bright;
        bright_min = bright;
        for (int i=0; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, parameters.CLKH);
        }
        for (int i=1; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, parameters.CLKM);
        }
        for (int i=2; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, CLKS);
        }
        for (int i=3; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, tmp);
        }
        for (int i=4; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, bright);
        }
    }else{
        if (tmp > temperature_max){
            temperature_max = tmp;
            DATAEE_WriteByte(EEAddr, parameters.CLKH);
            DATAEE_WriteByte(EEAddr + 1, parameters.CLKM);
            DATAEE_WriteByte(EEAddr + 2, CLKS);
            DATAEE_WriteByte(EEAddr + 3, tmp);
            DATAEE_WriteByte(EEAddr + 4, bright);
        }
        if (tmp < temperature_min){
            temperature_min = tmp;
            DATAEE_WriteByte(EEAddr + 5, parameters.CLKH);
            DATAEE_WriteByte(EEAddr + 6, parameters.CLKM);
            DATAEE_WriteByte(EEAddr + 7, CLKS);
            DATAEE_WriteByte(EEAddr + 8, tmp);
            DATAEE_WriteByte(EEAddr + 9, bright);
        }
        if (bright > bright_max){
            bright_max = bright;
            DATAEE_WriteByte(EEAddr + 10, parameters.CLKH);
            DATAEE_WriteByte(EEAddr + 11, parameters.CLKM);
            DATAEE_WriteByte(EEAddr + 12, CLKS);
            DATAEE_WriteByte(EEAddr + 13, tmp);
            DATAEE_WriteByte(EEAddr + 14, bright);
        }
        if (bright < bright_min){
            bright_min = bright;
            DATAEE_WriteByte(EEAddr + 15, parameters.CLKH);
            DATAEE_WriteByte(EEAddr + 16, parameters.CLKM);
            DATAEE_WriteByte(EEAddr + 17, CLKS);
            DATAEE_WriteByte(EEAddr + 18, tmp);
            DATAEE_WriteByte(EEAddr + 19, bright);
        }
    }

}
//Read the values stored on memory
void eeprom_read_records(uint16_t EEAddr, char buf1[17], char buf2[17], char buf3[17], char buf4[17]){
    
    sprintf(buf1, "%02d:%02d:%02d  %02dC L%d", DATAEE_ReadByte(EEAddr), DATAEE_ReadByte(EEAddr + 1), DATAEE_ReadByte(EEAddr + 2), DATAEE_ReadByte(EEAddr + 3), DATAEE_ReadByte(EEAddr + 4));
    sprintf(buf2, "%02d:%02d:%02d  %02dC L%d", DATAEE_ReadByte(EEAddr + 5), DATAEE_ReadByte(EEAddr + 6), DATAEE_ReadByte(EEAddr + 7), DATAEE_ReadByte(EEAddr + 8), DATAEE_ReadByte(EEAddr + 9));
    sprintf(buf3, "%02d:%02d:%02d  %02dC L%d", DATAEE_ReadByte(EEAddr + 10), DATAEE_ReadByte(EEAddr + 11), DATAEE_ReadByte(EEAddr + 12), DATAEE_ReadByte(EEAddr + 13), DATAEE_ReadByte(EEAddr + 14));
    sprintf(buf4, "%02d:%02d:%02d  %02dC L%d", DATAEE_ReadByte(EEAddr + 15), DATAEE_ReadByte(EEAddr + 16), DATAEE_ReadByte(EEAddr + 17), DATAEE_ReadByte(EEAddr + 18), DATAEE_ReadByte(EEAddr + 19));
}
