#include <drivers/pic.h>
#include <events/idt.h>
#include <events/irq.h>
#include <k/kstd.h>
#include <stdio.h>

irqhandler irq_handlers[16];

void irq_set_all_masks()
{
    irq_set_mask(0);
    irq_set_mask(1);
    irq_set_mask(2);
    irq_set_mask(3);
    irq_set_mask(4);
    irq_set_mask(5);
    irq_set_mask(6);
    irq_set_mask(7);
    irq_set_mask(8);
    irq_set_mask(9);
    irq_set_mask(10);
    irq_set_mask(11);
    irq_set_mask(12);
    irq_set_mask(13);
    irq_set_mask(14);
    irq_set_mask(15);
}

void add_irq_handler(u8 irq, irqhandler handler)
{
    asm volatile("cli");
    irq_handlers[irq] = handler;
    irq_clear_mask(irq);
    asm volatile("sti");
}

void remove_irq_handler(u8 irq)
{
    asm volatile("cli");
    irq_set_mask(irq);
    irq_handlers[irq] = NULL;
    asm volatile("sti");
}

void irq_handler(registers_t *regs)
{
    asm volatile("cli");
    if (irq_handlers[regs->int_no - 32] != NULL)
    {
        irq_handlers[regs->int_no - 32](regs);
    }
    pic_sendEOI(regs->int_no);
    asm volatile("sti");
}
