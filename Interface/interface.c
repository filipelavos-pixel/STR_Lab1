
#include "../mcc_generated_files/mcc.h"
#include "../LCD/lcd.h"
#include "interface.h"
#include "../Parameters_Block/parameters_block.h"
#include "../Clock/clock.h"
#include "../EEPROM/eeprom.h"

//Interface constructed for normal mode
void normal_interface(unsigned char tmp, uint8_t bright, bool alarm_clock, bool alarm_tmp, bool alarm_bright){
    
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
    if (alarm_tmp){
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
    sprintf(buf, "%02d C         L %d", tmp, bright);
    LCDstr(buf);
}

// interface on LCD for transition mode (2 seconds from normal mode to configuration)
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
// interface of configuration mode
void configuration_interface(uint8_t position, unsigned char tmp, uint8_t bright, bool current, bool editing_threshold) {
    
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
    // positions 0-2 show the clock or the alarm (current), C shows the alarm, the rest show the clock
    if ((position <= 2 && !current) || position == 3){
        sprintf(buf, "%02d:%02d:%02d  CTL %cR", parameters.ALAH, parameters.ALAM, parameters.ALAS, A);
    }
    else{
        sprintf(buf, "%02d:%02d:%02d  CTL %cR", parameters.CLKH, parameters.CLKM, CLKS, A);
    }
    LCDstr(buf);
    LCDcmd(0xc0);
    while (LCDbusy());
    // in T and L, show the threshold being edited instead of the current reading
    if (position == 4){
        sprintf(buf, "%02d C         L %d", parameters.ALAT, bright);
    }
    else if (position == 5){
        sprintf(buf, "%02d C         L %d", tmp, parameters.ALAL);
    }
    else{
        sprintf(buf, "%02d C         L %d", tmp, bright);
    }
    LCDstr(buf);

    // Underline cursor on the selected field.
    LCDcmd(0x0E);
    switch (position) {
        case 0: LCDpos(0, 1);  break;   // hh
        case 1: LCDpos(0, 4);  break;   // mm
        case 2: LCDpos(0, 7);  break;   // ss
        case 3: LCDpos(0, 10); break;   // C
        
        case 4: 
            if (editing_threshold) {
                LCDpos(1, 1);   // Temperature value.
            }
            else {
                LCDpos(0, 11);  // Letter T.
            }
            break;

        case 5: 
            if (editing_threshold) {
                LCDpos(1, 15);  // Luminosity value.
            }
            else {
                LCDpos(0, 12);  // Letter L.
            }
            break;

        case 6: LCDpos(0, 14); break;   // A
        case 7: LCDpos(0, 15); break;   // R
    }
}

// interface for max min values
void LCD_max_min(uint16_t EEAddr, uint8_t presentation_counter){
    
    char buf1[17], buf2[17], buf3[17], buf4[17];
    
    eeprom_read_records(EEAddr, buf1, buf2, buf3, buf4);
    
    switch (presentation_counter){
        case 0:
            LCDcmd(0x80);
            while (LCDbusy());
            LCDstr(buf1);
            LCDcmd(0xc0); 
            while (LCDbusy());
            LCDstr(buf2);
            break;
        case 1:
            LCDcmd(0x80);
            while (LCDbusy());
            LCDstr(buf3);
            LCDcmd(0xc0); 
            while (LCDbusy());
            LCDstr(buf4);
            break;
        default:
            break;
    }
}
