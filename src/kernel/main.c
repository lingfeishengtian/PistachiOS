#include "standard_types.h"
#include "kernel/peripherals/mini_uart.h"
#include "kernel/peripherals/uart.h"
#include "utils/printf.h"
#include "utils/utils.h"

volatile bool busy = false;
extern void _stack_init();

/**
 * @brief Configure current kernel debugging function.
 *
 * The printf for the whole kernel uses this internal _putchar statement. By changing this function, the whole kernel logging system is affected.
 * 
 * @param c The character to be logged
 */
void _putchar(char c){ uart0_putchar(c); }

void init_debug_utils(){
    init_uart();
    init_uart0();
}

void kernel_main(){
    init_debug_utils();
    printf("Current Exception Level: %d\n", kgetEL());

    wakeup_core(1, _stack_init);
    wakeup_core(2, _stack_init);
    wakeup_core(3, _stack_init);

    // Accept input
    while (1) {
        uart0_putchar(uart0_getchar());
    }
    return;
}

void secondary_cores_main(uint64_t processorID){
    while(busy){
        kdelay(10);
    }

    busy = true;
    printf("Processor %d loaded.\n", processorID);
    busy = false;

    return;
}