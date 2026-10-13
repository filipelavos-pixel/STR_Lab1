
#include "alarms.h"
#include "../Clock/clock.h"
#include "stdint.h"
#include "../Parameters_Block/parameters_block.h"

unsigned char alarm(unsigned char c, uint8_t bright){
    
    if (parameters.CLKH >= parameters.ALAH){
        if (parameters.CLKM >= parameters.ALAM){
            if(CLKS >= parameters.ALAS){
                return 'C';
            }
        }
    }
    if (c > parameters.ALAT){
        return 'T';
    }
    if (bright < parameters.ALAL){
        return 'L';
    }
    return '0';
}