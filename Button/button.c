
#include "../mcc_generated_files/mcc.h"
#include "../Parameters_Block/parameters_block.h"
#include "../Clock/clock.h"
#include "../EEPROM/eeprom.h"
#include "../Interface/interface.h"
#include "../LCD/lcd.h"
#include "../Sensors/sensors.h"

uint8_t S1_value; 
uint8_t S2_value;
uint8_t S1_state = 1;
bool S1_pressed = false;
uint8_t S2_state = 1;
bool S2_pressed = false;
uint8_t mode = 0;
uint8_t cursor_pos = 0; //cursor position for changing values or not

//if current true, open up changes to clock time
// if its false, button with cursor on C was pressed, so now we can change clock alarms
bool current = true;
uint8_t mode_count = 0; // count the two seconds in transition mode
uint8_t presentation_counter = 0; // count 1 second each, for printing on LCD the max min variables in right way

// type of alarm, if exists or not
bool alarm_clock = false;
bool alarm_tmp = false;
bool alarm_bright = false;

static uint8_t last_config_second = 255;

static bool editing_threshold = false;

/* S_State corresponds to the last value in get_value, we have to save it and
 * create more variables like S_pressed to do things in the right way
 * the while (1) makes this fucntion always go on loop in every microseconds
 * so if we press just one time the button, if we press more than the time
 * of one cycle, the program thinks we pressed a button more than on time
 * causing problems in the code, so we save the last value in S_state, and if
 * S_value (which is what GetValue catches in the moment) is different than
 * S_state, it means that we pressed the button one time (variation of value), 
 * so if that variation happens, S1_pressed is changed and remains true 
 * (if we really pressed the button one time) throughout just one cycle, 
 * in the next cycle S_pressed is turn false for blocking the program
 * to think we did more than one press on the button, so S_pressed just turns true
 * again if we press a button again.
*/

void button_control(uint16_t EEAddr, unsigned char tmp, uint8_t bright){
    
    //Value of o button in a moment
    S1_value = BUTTON_S1_GetValue();
    S2_value = BUTTON_S2_GetValue();
    S1_pressed = false;
    S2_pressed = false;

    if (S1_state == 1) {
        if (S1_value == 0) {
            S1_pressed = true;
        }
    }
    S1_state = S1_value;
    if (S2_state == 1) {
        if (S2_value == 0) {
            S2_pressed = true;
        }
    }
    S2_state = S2_value;
    // in configuration mode state (all modes are related to a interface function)
    if (mode == 2) {
        if (S1_pressed) {
            cursor_pos++;
            editing_threshold = false;
        }

        if (S2_pressed) {
            switch (cursor_pos) {
                case 0:
                    param_change = true; // CLKH or ALAH changes
                    if (current){
                        if (parameters.CLKH == 23){
                            parameters.CLKH = 0;
                            break;
                        }
                        parameters.CLKH++;
                    }
                    else{
                        if (parameters.ALAH == 23){
                            parameters.ALAH = 0;
                            break;
                        }                            
                        parameters.ALAH++;
                    }
                    break;
                case 1:
                    param_change = true; // CLKM or ALAM changes
                    if (current){
                        if (parameters.CLKM == 59){
                            parameters.CLKM = 0;
                            break;
                        }
                        parameters.CLKM++;
                    }
                    else{
                        if (parameters.ALAM == 59){
                            parameters.ALAM = 0;
                            break;
                        }
                        parameters.ALAM++;
                    }
                    break;
                case 2:
                    if (current){
                        if (CLKS == 59){
                            CLKS = 0;
                            break;
                        }
                        CLKS++;
                    }
                    else{
                        param_change = true; // CLKS is not saved, only ALAS
                        if (parameters.ALAS == 59){
                            parameters.ALAS = 0;
                            break;
                        }
                        parameters.ALAS++;
                    }
                    break;
                case 3:
                    cursor_pos = 0;
                    current = false;
                    break;
                case 4:
                    // First press: enter temperature editing without changing it.
                    if(!editing_threshold){
                        editing_threshold = true;
                        break;
                    }
                    
                    // Following presses: increment the temperature threshold.
                    param_change = true;

                    if (parameters.ALAT == 50) {
                        parameters.ALAT = 0;
                    } 

                    else {
                        parameters.ALAT++;
                    }

                    break;

                case 5:
                    // First press: enter luminosity editing without changing it.
                    if(!editing_threshold){
                        editing_threshold = true;
                        break;
                    }

                    // Following presses: increment the luminosity threshold.
                    param_change = true;

                    if (parameters.ALAL == 7){
                        parameters.ALAL = 0;
                    }

                    else {
                        parameters.ALAL++; 
                    }
                     
                    break;
                case 6:
                    param_change = true;
                    parameters.ALAF = !parameters.ALAF;
                    break;
                case 7: {
                    // Take a fresh sample as the new starting point.
                    unsigned char reset_tmp = readTC74();
                    uint8_t reset_bright = brightness();

                    // Reinitialize all four records using this sample.
                    eeprom_start = 0;
                    eeprom_record(EEAddr, reset_tmp, reset_bright);
                    break;
                }
                case 8:
                    break;
            }
        }

        if (cursor_pos >= 8) {
            cursor_pos = 0;
            mode = 0;
            LCDcmd(0x0C); // Hide the cursor outside configuration.
        }
        else {
            uint8_t current_second = CLKS;

            if (S1_pressed || S2_pressed || current_second != last_config_second) {

                last_config_second = current_second;
                configuration_interface(cursor_pos, tmp, bright, current, editing_threshold);
            }
        }
    }
    // in possible transition of normal to configurate mode
    else if (mode == 1){
        if (mode_count < 2){
            switch_interface();
            if (S1_pressed){
                mode = 2;
                mode_count = 0;
                last_config_second = 255; // forces the display to update
                cursor_pos = 0; // makes the cursor start at the hours field
                current = true; // makes sure the first clock we see on configuration mode is the current one
                editing_threshold = false;
            }
        }
        else{
            mode_count = 0;
            mode = 0;
        }

    }
    // normal mode
    else if (mode == 0){

        normal_interface(tmp, bright, alarm_clock, alarm_tmp, alarm_bright);
        if (S1_pressed){
            mode = 1;
            alarm_clock = false;
            alarm_tmp = false;
            alarm_bright = false;
        }
        if (S2_pressed){
            mode = 3;
        }
    }
    // max min temperature and bright mode
    else if (mode == 3){
        LCD_max_min(EEAddr, presentation_counter);
        if (presentation_counter >= 2){
            presentation_counter = 0;
            mode = 0;
        }
    }
}
