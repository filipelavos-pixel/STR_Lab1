
#include "alarms.h"
#include "../Clock/clock.h"
#include "stdint.h"

uint8_t ALAH = 12, ALAM = 0, ALAS = 0;
unsigned char ALAT = 25;
uint8_t ALAL = 3;

unsigned char alarm(unsigned char c, uint8_t bright){
    
    if (clk_h >= ALAH){
        if (clk_m >= ALAM){
            if(clk_s >= ALAS){
                return 'C';
            }
        }
    }
    if (c > ALAT){
        return 'T';
    }
    if (bright < ALAL){
        return 'L';
    }
    return 0;
}