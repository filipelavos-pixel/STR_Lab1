
#include "clock.h"
#include "stdbool.h"
#include "stdint.h"

volatile uint8_t clk_h = 0, clk_m = 0, clk_s = 0;
volatile bool tick_1s = false;

    void clock_isr(void) {
        clk_s++;
        if (clk_s >= 60) { 
            clk_s = 0;
            clk_m++;
            if (clk_m >= 60) { 
                clk_m = 0;
                clk_h++;
                if (clk_h >= 24) {
                    clk_h = 0; 
                }
            } 
        }
        tick_1s = true;
    }
