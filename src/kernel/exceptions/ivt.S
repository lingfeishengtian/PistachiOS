#include "kernel/exceptions/interrupts.h"

hang1:
	b hang1

.macro handle_exception type
.align 7
sub	sp, sp, #REGISTER_SIZES
stp	x28, x29, [sp, #16 * 14]
str	x30, [sp, #16 * 15]

bl  _finish_reg_store
mov	x0, #\type
mrs	x1, esr_el1
mrs	x2, elr_el1
mov x3, sp
bl  interrupt_handler
b   load_reg
.endm

_finish_reg_store:
	stp	x0, x1, [sp, #16 * 0]
	stp	x2, x3, [sp, #16 * 1]
	stp	x4, x5, [sp, #16 * 2]
	stp	x6, x7, [sp, #16 * 3]
	stp	x8, x9, [sp, #16 * 4]
	stp	x10, x11, [sp, #16 * 5]
	stp	x12, x13, [sp, #16 * 6]
	stp	x14, x15, [sp, #16 * 7]
	stp	x16, x17, [sp, #16 * 8]
	stp	x18, x19, [sp, #16 * 9]
	stp	x20, x21, [sp, #16 * 10]
	stp	x22, x23, [sp, #16 * 11]
	stp	x24, x25, [sp, #16 * 12]
	stp	x26, x27, [sp, #16 * 13]
    ret

load_reg:
	ldp	x0, x1, [sp, #16 * 0]
	ldp	x2, x3, [sp, #16 * 1]
	ldp	x4, x5, [sp, #16 * 2]
	ldp	x6, x7, [sp, #16 * 3]
	ldp	x8, x9, [sp, #16 * 4]
	ldp	x10, x11, [sp, #16 * 5]
	ldp	x12, x13, [sp, #16 * 6]
	ldp	x14, x15, [sp, #16 * 7]
	ldp	x16, x17, [sp, #16 * 8]
	ldp	x18, x19, [sp, #16 * 9]
	ldp	x20, x21, [sp, #16 * 10]
	ldp	x22, x23, [sp, #16 * 11]
	ldp	x24, x25, [sp, #16 * 12]
	ldp	x26, x27, [sp, #16 * 13]
	ldp	x28, x29, [sp, #16 * 14]
	ldr	x30, [sp, #16 * 15] 
	add	sp, sp, #REGISTER_SIZES		
	eret

.align 11
.globl _ivt
_ivt:
    handle_exception SYNC_EL1t
    handle_exception IRQ_EL1t
    handle_exception FIQ_EL1t
    handle_exception ERROR_EL1t

    handle_exception SYNC_EL1h
    handle_exception IRQ_EL1h
    handle_exception FIQ_EL1h
    handle_exception ERROR_EL1h

    handle_exception SYNC_EL0_64
    handle_exception IRQ_EL0_64
    handle_exception FIQ_EL0_64
    handle_exception ERROR_EL0_64

    handle_exception SYNC_EL0_32
    handle_exception IRQ_EL0_32
    handle_exception FIQ_EL0_32
    handle_exception ERROR_EL0_32