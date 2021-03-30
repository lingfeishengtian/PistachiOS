#include "standard_types.h"
#include "kernel/peripherals/mini_uart.h"
#include "kernel/peripherals/uart.h"
#include "utils/printf.h"
#include "utils/utils.h"

/**
 * @brief Configure current kernel debugging function.
 *
 * The printf for the whole kernel uses this internal _putchar statement. By changing this function, the whole kernel logging system is affected.
 * 
 * @param c The character to be logged
 */
void _putchar(char c){ uart_putchar(c); }

void init_debug_utils(){
    init_uart0();
    init_uart();
}

void kernel_main(){
    init_debug_utils();
    uart0_putchar('f');
    printf("Current Exception Level: %d", kgetEL());

    // Accept input
    // while (1) {
    //     uart0_putchar(uart0_getchar());
    // }
    return;
}

void secondary_cores_main(uint64_t processorID){
    printf("Processor %d loaded.", processorID);
}