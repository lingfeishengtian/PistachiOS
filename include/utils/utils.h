#ifndef P_OS_INCLUDE_UTILS_UTILS_H
#define P_OS_INCLUDE_UTILS_UTILS_H

#include "standard_types.h"

/**
 * @brief Stores a 32 bit value in a 64 bit address.
 *
 * Can be used for configuring data in memory-mapped peripherals. This function is programmed in assembly.
 * 
 * @param addr The 64-bit address to the peripheral configuration
 * @param data The 32-bit data to store
 */
extern void kput32(uint64_t addr, uint32_t data);

/**
 * @brief Loads a 32 bit value from a 64 bit address.
 *
 * Can be used for viewing the configuration of peripherals. This function is programmed in assembly.
 * 
 * @param addr The 64-bit address to the peripheral configuration
 * @return uint32_t Returns the config data located at this memory location
 */
extern uint32_t kget32(uint64_t addr);

/**
 * @brief Delays the program for a certain amount of clock cycles.
 *
 * Used to stall the program for certain setups, for example, the GPIO Pull-up/down Clock Registers.
 * 
 * @param cycles The amount of cycles to stall the program for.
 */
extern void kdelay(uint64_t cycles);

/**
 * @brief Get the current exception level
 * 
 * The current exception level describes the priveliges the program has.
 * 1) User
 * 2) Kernel
 * 3) Hypervisor
 *
 * @return uint64_t Return the exception level
 */
extern uint64_t kgetEL();

#endif /* P_OS_INCLUDE_UTILS_UTILS_H */
