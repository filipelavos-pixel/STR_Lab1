
#include "../LCD/lcd.h"
#include "interface.h"
#include "../Parameters_Block/parameters_block.h"
#include "../Clock/clock.h"

void normal_interface(unsigned char c, uint8_t bright, bool alarm_clock, bool alarm_c, bool alarm_bright){
    
    char buf[17];
    unsigned char A;
    unsigned char C;
    unsigned char T;
    unsigned char L;
 
    if (alarm_clock){
        C = 'C';
    }
    else{
        C = ' ';
    }
    if (alarm_c){
        T = 'T';
    }
    else{
        T = ' ';
    }
    if (alarm_bright){
        L = 'L';
    }
    else{
        L = ' ';
    } 
    if (parameters.ALAF == 0){
        A = 'a';
    }
    else if (parameters.ALAF == 1){
        A = 'A';
    }
    LCDcmd(0x80);       //first line, first column
    while (LCDbusy());
    sprintf(buf, "%02d:%02d:%02d  %c%c%c %c ", parameters.CLKH, parameters.CLKM, CLKS, C, T, L, A);
    LCDstr(buf);
    LCDcmd(0xc0);       // second line, first column
    while (LCDbusy());
    sprintf(buf, "%02d C         L %d", c, bright);
    LCDstr(buf);
}
