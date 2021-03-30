#include "kernel/boot/sysreg_conf.h"

.section ".text.boot"

.global _start

_start:
    mrs     x1, mpidr_el1   // Read the Multiprocessor Affinity Register EL1
    and     x1, x1, #0xFF   // Retrieve the bottom 8 bits which specify the processor and set the compare flag
    cbz     x1, preboot     // If compare flag is 0, then move to boot
hang:                       // Else hang
    b       hang

// Pre-Boot changes the exception level from 2 to 1 (since we are on qemu)
preboot:
	ldr	x0, =SCTLR_VALUE_MMU_DISABLED   
	msr	sctlr_el1, x0		

    ldr x0, = CPACR_VALUE
    msr CPACR_EL1, x0

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0
    
	adr	x0, boot		
	msr	elr_el2, x0

	ldr	x0, =SPSR_VALUE
	msr	spsr_el2, x0

	eret	

boot:
    // set stack before code
    ldr     x1, =_start
    mov     sp, x1

    // clear bss
    ldr     x1, =__bss_start    // Store start address of bss at w1
    ldr     w2, =__bss_size     // Store size of the bss at w2

clear_bss_loop:
    cbz     w2, jmp_kernel      // If size = 0 then start kernel
    str     xzr, [x1], #8       // Store a 0 into the current bss address and add 8 to the address
    subs    w2, w2, #1          // Subtract 1 from the size (since the linker file shifted three times to the right) and set condition flag
    bgt     clear_bss_loop      // If the size is greater than 0, continue clearing bss

    // jump to C code, should not return
jmp_kernel:  
    bl      kernel_main
    // for failsafe, halt this core too
    b       hang