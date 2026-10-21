
#include "clock.h"
#include "stdbool.h"
#include "stdint.h"
#include "../Parameters_Block/parameters_block.h"

volatile uint8_t CLKS = 0;
volatile bool tick_1s = false;

//function that calculates the clock time
    void clock_isr(void) {
        CLKS++;
        if (CLKS >= 60) { 
            CLKS = 0;
            parameters.CLKM++;
            param_change = true;
            if (parameters.CLKM >= 60) {
                parameters.CLKM = 0;
                parameters.CLKH++;
                if (parameters.CLKH >= 24) {
                    parameters.CLKH = 0; 
                }
            } 
        }
        tick_1s = true;
    }
