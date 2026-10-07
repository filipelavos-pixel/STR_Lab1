# 1 "EEPROM/eeprom.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "D:\\STR\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "EEPROM/eeprom.c" 2
# 1 "EEPROM/../mcc_generated_files/memory.h" 1
# 54 "EEPROM/../mcc_generated_files/memory.h"
# 1 "D:\\STR\\pic\\include\\c99/stdbool.h" 1 3
# 55 "EEPROM/../mcc_generated_files/memory.h" 2
# 1 "D:\\STR\\pic\\include\\c99/stdint.h" 1 3



# 1 "D:\\STR\\pic\\include\\c99/musl_xc8.h" 1 3
# 5 "D:\\STR\\pic\\include\\c99/stdint.h" 2 3
# 26 "D:\\STR\\pic\\include\\c99/stdint.h" 3
# 1 "D:\\STR\\pic\\include\\c99/bits/alltypes.h" 1 3
# 133 "D:\\STR\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned short uintptr_t;
# 148 "D:\\STR\\pic\\include\\c99/bits/alltypes.h" 3
typedef short intptr_t;
# 164 "D:\\STR\\pic\\include\\c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 194 "D:\\STR\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "D:\\STR\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "D:\\STR\\pic\\include\\c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "D:\\STR\\pic\\include\\c99/stdint.h" 3
# 1 "D:\\STR\\pic\\include\\c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "D:\\STR\\pic\\include\\c99/stdint.h" 2 3
# 56 "EEPROM/../mcc_generated_files/memory.h" 2
# 99 "EEPROM/../mcc_generated_files/memory.h"
uint16_t FLASH_ReadWord(uint16_t flashAddr);
# 128 "EEPROM/../mcc_generated_files/memory.h"
void FLASH_WriteWord(uint16_t flashAddr, uint16_t *ramBuf, uint16_t word);
# 164 "EEPROM/../mcc_generated_files/memory.h"
int8_t FLASH_WriteBlock(uint16_t writeAddr, uint16_t *flashWordArray);
# 189 "EEPROM/../mcc_generated_files/memory.h"
void FLASH_EraseBlock(uint16_t startAddr);
# 222 "EEPROM/../mcc_generated_files/memory.h"
void DATAEE_WriteByte(uint16_t bAdd, uint8_t bData);
# 248 "EEPROM/../mcc_generated_files/memory.h"
uint8_t DATAEE_ReadByte(uint16_t bAdd);
# 2 "EEPROM/eeprom.c" 2
# 1 "EEPROM/../Clock/clock.h" 1
# 19 "EEPROM/../Clock/clock.h"
extern volatile uint8_t clk_h;
extern volatile uint8_t clk_m;
extern volatile uint8_t clk_s;
extern volatile _Bool tick_1s;

void clock_isr(void);
# 3 "EEPROM/eeprom.c" 2
# 1 "EEPROM/eeprom.h" 1
# 17 "EEPROM/eeprom.h"
extern unsigned char temperature_max;
extern unsigned char temperature_min;
extern uint8_t bright_max;
extern uint8_t bright_min;
extern char eeprom_start;


void eeprom_record(uint16_t EEadr, unsigned char c, uint8_t bright);
# 4 "EEPROM/eeprom.c" 2


unsigned char temperature_max;
unsigned char temperature_min;
uint8_t bright_max;
uint8_t bright_min;
char eeprom_start = 0;

void eeprom_record(uint16_t EEAddr, unsigned char c, uint8_t bright) {

    if (eeprom_start == 0){
        eeprom_start = 1;
        temperature_max = c;
        temperature_min = c;
        bright_max = bright;
        bright_min = bright;
        for (int i=0; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, clk_h);
        }
        for (int i=1; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, clk_m);
        }
        for (int i=2; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, clk_s);
        }
        for (int i=3; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, c);
        }
        for (int i=4; i<20; i=i+5){
            DATAEE_WriteByte(EEAddr + i, bright);
        }
    }else{
        if (c > temperature_max){
            temperature_max = c;
            DATAEE_WriteByte(EEAddr, clk_h);
            DATAEE_WriteByte(EEAddr + 1, clk_m);
            DATAEE_WriteByte(EEAddr + 2, clk_s);
            DATAEE_WriteByte(EEAddr + 3, c);
            DATAEE_WriteByte(EEAddr + 4, bright);
        }
        if (c < temperature_min){
            temperature_min = c;
            DATAEE_WriteByte(EEAddr + 5, clk_h);
            DATAEE_WriteByte(EEAddr + 6, clk_m);
            DATAEE_WriteByte(EEAddr + 7, clk_s);
            DATAEE_WriteByte(EEAddr + 8, c);
            DATAEE_WriteByte(EEAddr + 9, bright);
        }
        if (bright > bright_max){
            bright_max = bright;
            DATAEE_WriteByte(EEAddr + 10, clk_h);
            DATAEE_WriteByte(EEAddr + 11, clk_m);
            DATAEE_WriteByte(EEAddr + 12, clk_s);
            DATAEE_WriteByte(EEAddr + 13, c);
            DATAEE_WriteByte(EEAddr + 14, bright);
        }
        if (bright < bright_min){
            bright_min = bright;
            DATAEE_WriteByte(EEAddr + 15, clk_h);
            DATAEE_WriteByte(EEAddr + 16, clk_m);
            DATAEE_WriteByte(EEAddr + 17, clk_s);
            DATAEE_WriteByte(EEAddr + 18, c);
            DATAEE_WriteByte(EEAddr + 19, bright);
        }
    }

}
