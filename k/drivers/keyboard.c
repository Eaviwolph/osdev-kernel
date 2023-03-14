#include <k/types.h>
#include <events/idt.h>
#include <events/irq.h>
#include <k/kstd.h>
#include "../io.h"
#include <stdio.h>

const char ascii_table[] = {'^', '^', '1', '2', '3', '4', '5', '6', '7', '8',
                            '9', '0', '-', '=', '^', '^', 'Q', 'W', 'E', 'R',
                            'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '^', '^',
                            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
                            '\'', '`', '^', '\\', 'Z', 'X', 'C', 'V', 'B', 'N',
                            'M', ',', '.', '/', '^', '^', '^', ' '};

int last_key = -1;

int getkey(void)
{
    int key_to_ret = last_key;
    last_key = -1;
    if (key_to_ret == -1)
    {
        return -1;
    }
    return ascii_table[key_to_ret];
}

void keyboard_handler(registers_t *regs)
{
    (void)regs;
    u8 scancode = inb(0x60);
    if (scancode & 0x80)
        return;
    last_key = scancode;
}

void keyboard_init(void)
{
    add_irq_handler(1, keyboard_handler);
}
