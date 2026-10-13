
#include "parameters_block.h"

// Alocação real da variável global
Config_Parameters parameters;

void DefaultParameters(void) {
    parameters.MW   = 0xA5;    // Palavra mágica
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
