.globl irq_vector_init
irq_vector_init:
    adr    x0, _ivt             // load VBAR_EL1 with vector
    msr    vbar_el1, x0        // vector table address
    ret

.globl unmask_irq
unmask_irq:
    msr    daifclr, #2
    ret

.globl mask_irq
mask_irq:
    msr    daifset, #2
    ret