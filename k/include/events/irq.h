#pragma once

#include <events/idt.h>

typedef void (*irqhandler)(registers_t *);

extern void irq_0();
extern void irq_1();
extern void irq_2();
extern void irq_3();
extern void irq_4();
extern void irq_5();
extern void irq_6();
extern void irq_7();
extern void irq_8();
extern void irq_9();
extern void irq_10();
extern void irq_11();
extern void irq_12();
extern void irq_13();
extern void irq_14();
extern void irq_15();

void irq_handler(registers_t *reg);
void add_irq_handler(u8 irq, irqhandler handler);
void remove_irq_handler(u8 irq);