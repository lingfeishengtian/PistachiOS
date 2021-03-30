#ifndef P_OS_KERNEL_PERIPHERALS_MINI_UART_H
#define P_OS_KERNEL_PERIPHERALS_MINI_UART_H

#include "base.h"

// From the BCM2837 ARM Peripheral Manual
#define AUX_ENABLES     (P_BASE+0x00215004)
#define AUX_MU_IO_REG   (P_BASE+0x00215040)
#define AUX_MU_IER_REG  (P_BASE+0x00215044)
#define AUX_MU_IIR_REG  (P_BASE+0x00215048)
#define AUX_MU_LCR_REG  (P_BASE+0x0021504C)
#define AUX_MU_MCR_REG  (P_BASE+0x00215050)
#define AUX_MU_LSR_REG  (P_BASE+0x00215054)
#define AUX_MU_MSR_REG  (P_BASE+0x00215058)
#define AUX_MU_SCRATCH  (P_BASE+0x0021505C)
#define AUX_MU_CNTL_REG (P_BASE+0x00215060)
#define AUX_MU_STAT_REG (P_BASE+0x00215064)
#define AUX_MU_BAUD_REG (P_BASE+0x00215068)

// Tell us what the data recieved by UART means
#define READ_DATA_RDY_UART1   (0x01)
#define WRITE_DATA_RDY_UART1  (0x20)

/**
 * @brief Initialize mini-UART
 * 
 * This function follows the BCM2837 Peripheral Manual on different configurations.
 */
void init_uart();

/**
 * @brief Puts a specific character into UART.
 * 
 * Similar to the C function putchar, this function puts a character into mini-UART.
 *
 * Since this function stores values into UART1, for qemu to display these values ```-serial null -serial mon:stdio``` are needed to view the values passed here.
 *
 * @param character The character to store
 */
void uart_putchar(char character);

/**
 * @brief Retrieves data from mini-UART.
 * 
 * Can be used to get keystrokes entered into UART1.
 *
 * @return char The character that was recieved
 */
char uart_getchar();

#endif /* P_OS_KERNEL_PERIPHERALS_MINI_UART_H */
