.extern isr_handler

.altmacro
.macro isr_ERR num
    .global isr_err_\num
    isr_err_\num:
        cli
        push $\num
        jmp exp_err_ctx_saver
.endm

isr_ERR 8

isr_ERR 10
isr_ERR 11
isr_ERR 12
isr_ERR 13
isr_ERR 14


exp_err_ctx_saver:
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
    call isr_handler
    addl $4, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popa

    addl $8, %esp
    iret
