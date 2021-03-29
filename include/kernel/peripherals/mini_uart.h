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

#define READ_DATA_RDY   (0x01)
#define WRITE_DATA_RDY  (0x20)

void init_uart();

void uart_putchar(char character);

char uart_getchar();

void uart_printf(char* str, ...);

#endif /* P_OS_KERNEL_PERIPHERALS_MINI_UART_H */
