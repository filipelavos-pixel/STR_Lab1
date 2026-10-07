# 1 "Clock/clock.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "D:\\STR\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Clock/clock.c" 2

# 1 "Clock/clock.h" 1
# 15 "Clock/clock.h"
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
# 16 "Clock/clock.h" 2
# 1 "D:\\STR\\pic\\include\\c99/stdbool.h" 1 3
# 17 "Clock/clock.h" 2


extern volatile uint8_t clk_h;
extern volatile uint8_t clk_m;
extern volatile uint8_t clk_s;
extern volatile _Bool tick_1s;

void clock_isr(void);
# 3 "Clock/clock.c" 2



volatile uint8_t clk_h = 0, clk_m = 0, clk_s = 0;
volatile _Bool tick_1s = 0;

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
        tick_1s = 1;
    }
