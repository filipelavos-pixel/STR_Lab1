
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

void switch_interface(){
    
    char buf[17];
    unsigned char A;
    if (parameters.ALAF == 0){
        A = 'a';
    }
    else if (parameters.ALAF == 1){
        A = 'A';
    }
    
    LCDcmd(0x80);       //first line, first column
    while (LCDbusy());
    sprintf(buf, "%02d:%02d:%02d  %c%c%c %c ", parameters.ALAH, parameters.ALAM, parameters.ALAS, ' ', ' ', ' ', A);
    LCDstr(buf);
    LCDcmd(0xc0);       // second line, first column
    while (LCDbusy());
    sprintf(buf, "%02d C         L %d", parameters.ALAT, parameters.ALAL);
    LCDstr(buf);
}
void configuration_interface(uint8_t position, unsigned char c, uint8_t bright, bool current){
    
    char buf[17];
    unsigned char A;
    if (parameters.ALAF == 0){
        A = 'a';
    }
    else if (parameters.ALAF == 1){
        A = 'A';
    }
    
    LCDcmd(0x80);        // Primeira linha, primeira coluna
    while (LCDbusy());
    
    switch (position) {
        case 0: 
            if (current){
                sprintf(buf, ">%02d:%02d:%02d CTL %cR", parameters.CLKH, parameters.CLKM, CLKS, A);
            }
            else{
                sprintf(buf, ">%02d:%02d:%02d CTL %cR", parameters.ALAH, parameters.ALAM, parameters.ALAS, A);
            }
            break;
        case 1: 
            if (current){
                sprintf(buf, "%02d:>%02d:%02d CTL %cR", parameters.CLKH, parameters.CLKM, CLKS, A);
            }
            else{
                sprintf(buf, "%02d:>%02d:%02d CTL %cR", parameters.ALAH, parameters.ALAM, parameters.ALAS, A);
            }
            break;
        case 2: 
            if (current){
                sprintf(buf, "%02d:%02d:>%02d CTL %cR", parameters.CLKH, parameters.CLKM, CLKS, A);
            }
            else{
                sprintf(buf, "%02d:%02d:>%02d CTL %cR", parameters.ALAH, parameters.ALAM, parameters.ALAS, A);
            }
            break;
        case 3: 
            sprintf(buf, "%02d:%02d:%02d >CTL %cR", parameters.ALAH, parameters.ALAM, parameters.ALAS, A);
            break;
        case 4: 
            sprintf(buf, "%02d:%02d:%02d C>TL %cR", parameters.CLKH, parameters.CLKM, CLKS, A);
            break;
        case 5: 
            sprintf(buf, "%02d:%02d:%02d CT>L %cR", parameters.CLKH, parameters.CLKM, CLKS, A);
            break;
        case 6: 
            sprintf(buf, "%02d:%02d:%02d CTL>%cR", parameters.CLKH, parameters.CLKM, CLKS, A);
            break;
        case 7: 
            sprintf(buf, "%02d:%02d:%02d CTL %c>R", parameters.CLKH, parameters.CLKM, CLKS, A);
            break;
    }
    LCDstr(buf);
    LCDcmd(0xc0);     
    while (LCDbusy());
    switch (position) {
        case 4:
            sprintf(buf, "%02d C        >L %d", parameters.ALAT, bright);
            break;
        case 5:
            sprintf(buf, "%02d C<        L %d", c, parameters.ALAL);
            break;
        default:
            sprintf(buf, "%02d C         L %d", c, bright);
            break;
    }
    LCDstr(buf);
    
}
