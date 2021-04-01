#ifndef P_OS_KERNEL_BOOT_SYSREG_CONF_H
#define P_OS_KERNEL_BOOT_SYSREG_CONF_H

// ***************************************
// SCTLR_EL1, System Control Register (EL1), Page 2654 of AArch64-Reference-Manual.
// ***************************************

#define SCTLR_RESERVED                  (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTLR_EE_LITTLE_ENDIAN          (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN         (0 << 24)
#define SCTLR_I_CACHE_DISABLED          (0 << 12)
#define SCTLR_D_CACHE_DISABLED          (0 << 2)
#define SCTLR_MMU_DISABLED              (0 << 0)
#define SCTLR_MMU_ENABLED               (1 << 0)

#define SCTLR_VALUE_MMU_DISABLED	(SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)

// ***************************************
// CPACR_EL1, Architectural Feature Access Control Register (EL1) Page 2411 of AArch64-Reference-Manual.
// ***************************************

#define CPACR_ALLOW_FP          (3 << 20)
#define CPACR_TRAP_SVE          (1 << 16)
#define CPACR_VALUE             (CPACR_ALLOW_FP | CPACR_TRAP_SVE)

// ***************************************
// HCR_EL2, Hypervisor Configuration Register (EL2), Page 2487 of AArch64-Reference-Manual.
// ***************************************

#define HCR_RW	    			(1 << 31)
#define HCR_VALUE			    HCR_RW

// ***************************************
// SPSR_EL2, Saved Program Status Register (EL2) Page 383 of AArch64-Reference-Manual.
// ***************************************

#define SPSR_MASK_ALL 			(7 << 6)
#define SPSR_EL1h			    (5 << 0)
#define SPSR_VALUE			    (SPSR_MASK_ALL | SPSR_EL1h)

#endif /* P_OS_KERNEL_BOOT_SYSREG_CONF_H */
