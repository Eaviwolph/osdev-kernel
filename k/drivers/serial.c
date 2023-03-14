#include <drivers/serial.h>
#include <k/kstd.h>
#include <stdio.h>

#include "../io.h"

#define COMM1 0x3F8

int is_transmit_empty()
{
    return inb(COMM1 + 5) & 0x20;
}

void write_char(char a)
{
    while (is_transmit_empty() == 0)
        ;
    outb(COMM1, a);
}

int write(char *buf, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        write_char(buf[i]);
    }

    return 0;
}

void set_dlab()
{
    outb(COMM1 + 3, inb(COMM1 + 3) | 0x80);
}

void clear_dlab()
{
    outb(COMM1 + 3, inb(COMM1 + 3) & 0x7F);
}

// Initializing through COMM1
int serial_init(void)
{
    // Setting baud rate at 38400 bps
    set_dlab();

    outb(COMM1 + 0, 0X03);
    outb(COMM1 + 1, 0X00);

    clear_dlab();

    // Interrupt Enable Register: Enable Transmitter Holding Register Empty
    // Interrupt
    outb(COMM1 + 1, 0x02);

    // FIFO Control Register: (FIFO) | (Interrupt trigger level 14 bytes) |
    // (Clear transmit FIFO) | (Clear receive FIFO) = 11000111
    outb(COMM1 + 2, 0xC7);

    // Line Control Register: (8 bits length) | (No parity) = 00000011
    outb(COMM1 + 3, 0x03);

    return 0;
}
