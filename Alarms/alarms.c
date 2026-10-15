
#include "alarms.h"
#include "../Clock/clock.h"
#include "stdint.h"
#include "../Parameters_Block/parameters_block.h"

//Returns the letter that corresponds to the alarm being activated by threshold conditions, if not, returns 0
unsigned char alarm(unsigned char tmp, uint8_t bright){
    
    if (parameters.CLKH >= parameters.ALAH){
        if (parameters.CLKM >= parameters.ALAM){
            if(CLKS >= parameters.ALAS){
                return 'C';
            }
        }
    }
    if (tmp > parameters.ALAT){
        return 'T';
    }
    if (bright < parameters.ALAL){
        return 'L';
    }
    return '0';
}