.extern isr_handler

.altmacro
.macro isr_NO_ERR num
    .global isr_no_err_\num
    isr_no_err_\num:
        cli
        push $0
        push $\num
        jmp exp_no_err_ctx_saver
.endm

isr_NO_ERR 0
isr_NO_ERR 1
isr_NO_ERR 2
isr_NO_ERR 3
isr_NO_ERR 4
isr_NO_ERR 5
isr_NO_ERR 6
isr_NO_ERR 7

isr_NO_ERR 9

isr_NO_ERR 15
isr_NO_ERR 16
isr_NO_ERR 17
isr_NO_ERR 18
isr_NO_ERR 19
isr_NO_ERR 20
isr_NO_ERR 21
isr_NO_ERR 22
isr_NO_ERR 23
isr_NO_ERR 24
isr_NO_ERR 25
isr_NO_ERR 26
isr_NO_ERR 27
isr_NO_ERR 28
isr_NO_ERR 29
isr_NO_ERR 30
isr_NO_ERR 31

isr_NO_ERR 128

exp_no_err_ctx_saver:
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
