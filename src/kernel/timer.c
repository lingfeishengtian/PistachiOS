#include "kernel/timer.h"
#include "kernel/exceptions/interrupts.h"
#include "standard_types.h"
#include "utils/utils.h"
#include "utils/printf.h"

// Call an interrupt every [interval] amount of clock cycles
const uint64_t interval = 1000000;
uint64_t compare_clock_val = 0;

void timer_init(){
    compare_clock_val = kget32(TIMER_CLO);
    compare_clock_val += interval;
    kput32(TIMER_C1, compare_clock_val);
}

void handle_timer_int(){
    compare_clock_val += interval;
    kput32(TIMER_C1, compare_clock_val);
    kput32(TIMER_CS, TIMER_CS_M1);

    printf("Timer interrupt - Next interrupt at %d clock cycles.\n", compare_clock_val);
}