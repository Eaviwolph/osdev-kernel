#include <events/syscall.h>
#include <events/isr.h>
#include <stdio.h>

char *exception_messages[32] =
    {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",
        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"};

void isr_handler(registers_t *regs)
{
    if (regs->int_no == 0x80)
    {
        printf("INT NUM: %d\r\n", regs->eax);
        syscall_handler(regs);
    }
    else
    {
        printf("EXCEPTION: %s\r\n", exception_messages[regs->int_no]);
    }
}