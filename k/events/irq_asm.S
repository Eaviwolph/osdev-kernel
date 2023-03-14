.extern irq_handler

.altmacro
.macro IRQ num byt
    .global irq_\num
    irq_\num:
        cli
        push $0
        push $\byt
        jmp irq_ctx_saver
.endm

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

irq_ctx_saver:
    pusha

    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    cld

    push %esp
    call irq_handler
    addl $4, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popa

    addl $8, %esp
    iret
