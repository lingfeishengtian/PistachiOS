section ".text"

.globl _entry
_entry:
    mov sp, end
    bl kernel_main
_hang:    
    b _hang