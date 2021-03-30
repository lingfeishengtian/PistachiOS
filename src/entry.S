#include "kernel/boot/sysreg_conf.h"
#include "kernel/boot/mm.h"

.section ".text.boot"

.global _start
.global _stack_init

_start:
    mrs     x0, mpidr_el1   // Read the Multiprocessor Affinity Register EL1
    and     x0, x0, #0xFF   // Retrieve the bottom 8 bits which specify the processor and set the compare flag
    adr     x1, boot
    cbz     x0, _preboot     // If compare flag is 0, then move to boot
    wfe
    b       _stack_init

// Pre-Boot changes the exception level from 2 to 1 (since we are on qemu)
// Additionally returns to the address specified by x1
_preboot:
	ldr	x0, =SCTLR_VALUE_MMU_DISABLED   
	msr	sctlr_el1, x0		

    ldr x0, = CPACR_VALUE
    msr CPACR_EL1, x0

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0
    	
	msr	elr_el2, x1

	ldr	x0, =SPSR_VALUE
	msr	spsr_el2, x0

	eret	

boot:
    // clear bss
    sev
    ldr     x1, =__bss_start    // Store start address of bss at w1
    ldr     w2, =__bss_size     // Store size of the bss at w2

clear_bss_loop:
    cbz     w2, _stack_init      // If size = 0 then start kernel
    str     xzr, [x1], #8       // Store a 0 into the current bss address and add 8 to the address
    subs    w2, w2, #1          // Subtract 1 from the size (since the linker file shifted three times to the right) and set condition flag
    bgt     clear_bss_loop      // If the size is greater than 0, continue clearing bss

_stack_init:
    mrs	    x0, mpidr_el1       // Check processor ID
	and	    x0, x0, #0xFF       // Take only bottom 8 bits

	mov	    x1, #SECTION_SIZE   
	mul	    x1, x1, x0
	add	    x1, x1, #LOW_MEMORY
	mov	    sp, x1              // Based on the processor ID, set a different stack address

    cbz     x0, jmp_kernel      // If processor 0, initialize kernel

    mov     x2, x0              // Otherwise, store processor ID in x2 (need later)
    bl      kgetEL              // Get exception level, since may have not changed to 1 yet
    cmp     x0, #1              // Compare with 1

    mov     x0, x2              // Restore processor ID to x0 for _preboot first parameter
    adr     x1, _stack_init     // Store _stack_init as the return address for _preboot second parameter
    bne     _preboot            // Call _preboot and rerun _stack_init

    bl      secondary_cores_main    // Call secondary cores main function
    b       hang

    // jump to C code, should not return
jmp_kernel:  
    bl      kernel_main
    // for failsafe, halt this core too
hang:
    b       hang