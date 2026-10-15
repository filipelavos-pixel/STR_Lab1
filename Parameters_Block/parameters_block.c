
#include "../mcc_generated_files/mcc.h"
#include "parameters_block.h"


Config_Parameters parameters;
// Set when a parameter changes (buttons or clock ISR), main loop saves it
volatile bool param_change = false;

//Default parameters initialized
void DefaultParameters(void) {
    parameters.MW   = MAGIC_WORD;  
    parameters.PMON = 5;
    parameters.TALA = 3;
    parameters.ALAF = 0;
    parameters.ALAH = 12;
    parameters.ALAM = 0;
    parameters.ALAS = 0;
    parameters.ALAT = 25;
    parameters.ALAL = 3;
    parameters.CLKH = 0;
    parameters.CLKM = 0;
}

//Checksum: sum (mod 256) of every byte from MW to CLKM
uint8_t params_checksum(Config_Parameters *p) {
    uint8_t *b = (uint8_t *) p;
    uint8_t sum = 0;
    for (uint8_t i = 0; i < sizeof(Config_Parameters) - 1; i++) {
        sum += b[i];
    }
    return sum;
}

//Save the parameters block at the begin of the EEPROM (only the bytes that changed)
void params_save(void) {
    Config_Parameters params_s = parameters;
    uint8_t *b = (uint8_t *) &params_s;

    params_s.MW = MAGIC_WORD;
    params_s.checksum = params_checksum(&params_s);

    for (uint8_t i = 0; i < sizeof(Config_Parameters); i++) {
        if (DATAEE_ReadByte(PARAMS_ADDR + i) != b[i]) {
            DATAEE_WriteByte(PARAMS_ADDR + i, b[i]);
        }
    }
}

//Load the parameters block from the EEPROM, true if MW and checksum are valid
bool params_load(void) {
    Config_Parameters saved;
    uint8_t *b = (uint8_t *) &saved;

    for (uint8_t i = 0; i < sizeof(Config_Parameters); i++) {
        b[i] = DATAEE_ReadByte(PARAMS_ADDR + i);
    }
    if (saved.MW != MAGIC_WORD || saved.checksum != params_checksum(&saved)) {
        return false;
    }
    parameters = saved;
    return true;
}
