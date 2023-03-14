#include <drivers/pic.h>

#include "../io.h"

void pic_init()
{
    unsigned char a1 = inb(PIC1_DATA);
    outb(0x80, 0); // WAIT PIC
    unsigned char a2 = inb(PIC2_DATA);
    outb(0x80, 0);

    outb(PIC1_COMMAND, ICW1);
    outb(0x80, 0);
    outb(PIC2_COMMAND, ICW1);
    outb(0x80, 0);

    outb(PIC1_DATA, ICW2_MASTER_PIC_V_OFFSET);
    outb(0x80, 0);
    outb(PIC2_DATA, ICW2_SLAVE_PIC_V_OFFSET);
    outb(0x80, 0);

    outb(PIC1_DATA, 0x4);
    outb(0x80, 0);
    outb(PIC2_DATA, 0x2);
    outb(0x80, 0);

    outb(PIC1_DATA, ICW4_8086);
    outb(0x80, 0);
    outb(PIC2_DATA, ICW4_8086);
    outb(0x80, 0);

    outb(PIC1_DATA, a1);
    outb(0x80, 0);
    outb(PIC2_DATA, a2);
    outb(0x80, 0);
}

void pic_sendEOI(u8 irq)
{
    if (irq >= 8)
        outb(PIC2, PIC_EOI);
    outb(PIC1, PIC_EOI);
}

void irq_set_mask(u8 IRQline)
{
    u16 port;
    u8 value;

    if (IRQline < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);
}

void irq_clear_mask(u8 IRQline)
{
    u16 port;
    u8 value;

    if (IRQline < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);
}