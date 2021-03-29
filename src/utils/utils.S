.section ".text"

.globl kput32
kput32:
    str w1, [x0]
    ret

.globl kget32
kget32:
    ldr w0, [x0]
    ret

.globl kdelay
kdelay:
    subs x0, x0, #1
    bne kdelay
    ret