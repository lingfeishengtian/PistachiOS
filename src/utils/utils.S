.section ".text"

/*
 * All of the functions in this file are defined in the header utils.h
 *
 * These functions are for IO and contain basic functions that store or load data to or from a specified address.
 */

.globl kput32
kput32:
    str w1, [x0]        // Store the second parameter into the address specified by the first parameter
    ret                 // return

.globl kget32
kget32:
    ldr w0, [x0]        // Load the data from the first parameter into the return data
    ret                 // return

.globl kdelay
kdelay:
    subs x0, x0, #1     // Subtracted one from the first parameter
    bne kdelay          // If the number in the first parameter is not 0, then run again
    ret                 // return

.globl kgetEL
kgetEL:
    mrs x0, CurrentEL   // Store the current exception level into the return register
    lsr x0, x0, #2      // Shift the EL right by 2 as the first 2 bits are always 0
    ret                 // return

.globl wakeup_core
wakeup_core:
	mov x2, 0xd8
	str x1, [x2, x0, LSL #3]
	sev
	ret