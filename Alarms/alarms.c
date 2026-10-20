
#include "alarms.h"
#include "../Clock/clock.h"
#include "stdint.h"
#include "stdbool.h"
#include "../Parameters_Block/parameters_block.h"
#include "../Button/button.h"

// Checks each alarm condition independently and sets its flag (C, T, L)
// Returns true if a new alarm was raised (flag went from false to true)
bool alarm(unsigned char tmp, uint8_t bright){
    bool new_alarm = false;

    // Raise the clock alarm at the configured time.
    if (!alarm_clock &&
        parameters.CLKH == parameters.ALAH &&
        parameters.CLKM == parameters.ALAM &&
        CLKS == parameters.ALAS) {

        alarm_clock = true;
        new_alarm = true;
    }
    if (!alarm_tmp && tmp > parameters.ALAT){
        alarm_tmp = true;
        new_alarm = true;
    }
    if (!alarm_bright && bright < parameters.ALAL){
        alarm_bright = true;
        new_alarm = true;
    }
    return new_alarm;
}
