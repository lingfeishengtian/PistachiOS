#ifndef P_OS_KERNEL_PERIPHERALS_BASE_H
#define P_OS_KERNEL_PERIPHERALS_BASE_H

#define P_BASE 0x3F000000

// From the BCM2837 ARM Peripheral Manual
#define GPFSEL1         (P_BASE+0x00200004)
#define GPSET0          (P_BASE+0x0020001C)
#define GPCLR0          (P_BASE+0x00200028)
#define GPPUD           (P_BASE+0x00200094)
#define GPPUDCLK0       (P_BASE+0x00200098)

#endif /* P_OS_KERNEL_PERIPHERALS_BASE_H */