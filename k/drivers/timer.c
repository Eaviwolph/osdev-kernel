#include <drivers/timer.h>
#include <events/irq.h>
#include <events/idt.h>
#include "../io.h"

static unsigned long tick = 0;

unsigned long gettick(void)
{
    return tick;
}

void timer_handler(registers_t *regs)
{
    (void)regs;
    tick++;
}
void timer_init(void)
{
    outb(0x43, 0x34); // CHANNEL0 | lobyte/hibyte | Mode 2 | 16-bit binary
    u16 divisor = INTERNAL_FREQUENCY / 100;

    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);

    add_irq_handler(0, timer_handler);
}
