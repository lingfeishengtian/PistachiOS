#ifndef P_OS_KERNEL_PERIPHERALS_UART0_H
#define P_OS_KERNEL_PERIPHERALS_UART0_H

#include "standard_types.h"
#include "base.h"

// From the PL011 ARM Manual
#define UART0_BASE      (P_BASE + 0x201000)

#define UART0_DR	    (UART0_BASE+0)
#define UART0_RSRECR	(UART0_BASE+0x4)
#define UART0_FR    	(UART0_BASE+0x18)
#define UART0_IBRD	    (UART0_BASE+0x24)
#define UART0_FBRD	    (UART0_BASE+0x28)
#define UART0_LCRH	    (UART0_BASE+0x2c)
#define UART0_CR	    (UART0_BASE+0x30)
#define UART0_IMSC      (UART0_BASE+0x38)
#define UART0_ICR       (UART0_BASE + 0x44)

// Tell us what the data recieved by UART means
#define READ_DATA_RDY_UART0   (0x10)
#define WRITE_DATA_RDY_UART0  (0x20)

// Calculate the baud rate related properties. Reference from manual page 3-10
#define UART0_CLOCK     	48000000ul
#define UART0_BAUD(br)      (((UART0_CLOCK) / (16.0 * (br))))
#define UART0_BAUD_115200	UART0_BAUD(115200ul)
#define UART0_IBRD_115200	((unsigned int)UART0_BAUD_115200)
#define UART0_FBRD_115200	((unsigned int)(((UART0_BAUD_115200-UART0_IBRD_115200) * 64) + 0.5))

/**
 * @brief Initialize mini-UART
 * 
 * This function follows the PL011 Peripheral Manual on different configurations.
 */
void init_uart0();

/**
 * @brief Puts a specific character into UART.
 * 
 * Similar to the C function putchar, this function puts a character into mini-UART.
 *
 * Since this function stores values into UART0.
 *
 * @param character The character to store
 */
void uart0_putchar(char character);

/**
 * @brief Retrieves data from mini-UART.
 * 
 * Can be used to get keystrokes entered into UART0.
 *
 * @return char The character that was recieved
 */
char uart0_getchar();

#endif /* P_OS_KERNEL_PERIPHERALS_UART0_H */
