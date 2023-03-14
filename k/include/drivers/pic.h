#pragma once

#include <k/types.h>

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)
#define PIC_EOI 0x20

#define ICW4_8086 0x01

#define ICW2_MASTER_PIC_V_OFFSET 0x20
#define ICW2_SLAVE_PIC_V_OFFSET 0x28

#define ICW1 0x11
#define ICW4 0x01

void pic_init();
void pic_sendEOI(u8 irq);

void irq_set_mask(unsigned char IRQline);
void irq_clear_mask(unsigned char IRQline);
