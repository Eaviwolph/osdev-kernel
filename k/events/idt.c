#include <events/idt.h>
#include <events/irq.h>
#include <events/isr.h>
#include <string.h>

struct idt idt[IDT_ENTRIES_NUM];
struct idtr idtr;

void init_idt_entry(struct idt *t, u32 base, u16 sel, u8 flags)
{
    t->offset_15_0 = base & 0xFFFF;
    t->offset_31_16 = (base >> 16) & 0xFFFF;
    t->gate_type = 0;
    t->seg_selector = sel;
    t->flags = flags;
}

void idt_init()
{
    memset(idt, 0, sizeof(idt));
    idtr.base = (u32)idt;
    idtr.limit = sizeof(idt) - 1;

    init_idt_entry(&idt[0], (u32)isr_no_err_0, 0x08, 0x8E);
    init_idt_entry(&idt[1], (u32)isr_no_err_1, 0x08, 0x8E);
    init_idt_entry(&idt[2], (u32)isr_no_err_2, 0x08, 0x8E);
    init_idt_entry(&idt[3], (u32)isr_no_err_3, 0x08, 0x8E);
    init_idt_entry(&idt[4], (u32)isr_no_err_4, 0x08, 0x8E);
    init_idt_entry(&idt[5], (u32)isr_no_err_5, 0x08, 0x8E);
    init_idt_entry(&idt[6], (u32)isr_no_err_6, 0x08, 0x8E);
    init_idt_entry(&idt[7], (u32)isr_no_err_7, 0x08, 0x8E);

    init_idt_entry(&idt[8], (u32)isr_err_8, 0x08, 0x8E);

    init_idt_entry(&idt[9], (u32)isr_no_err_9, 0x08, 0x8E);

    init_idt_entry(&idt[10], (u32)isr_err_10, 0x08, 0x8E);
    init_idt_entry(&idt[11], (u32)isr_err_11, 0x08, 0x8E);
    init_idt_entry(&idt[12], (u32)isr_err_12, 0x08, 0x8E);
    init_idt_entry(&idt[13], (u32)isr_err_13, 0x08, 0x8E);
    init_idt_entry(&idt[14], (u32)isr_err_14, 0x08, 0x8E);

    init_idt_entry(&idt[15], (u32)isr_no_err_15, 0x08, 0x8E);
    init_idt_entry(&idt[16], (u32)isr_no_err_16, 0x08, 0x8E);
    init_idt_entry(&idt[17], (u32)isr_no_err_17, 0x08, 0x8E);
    init_idt_entry(&idt[18], (u32)isr_no_err_18, 0x08, 0x8E);
    init_idt_entry(&idt[19], (u32)isr_no_err_19, 0x08, 0x8E);
    init_idt_entry(&idt[20], (u32)isr_no_err_20, 0x08, 0x8E);
    init_idt_entry(&idt[21], (u32)isr_no_err_21, 0x08, 0x8E);
    init_idt_entry(&idt[22], (u32)isr_no_err_22, 0x08, 0x8E);
    init_idt_entry(&idt[23], (u32)isr_no_err_23, 0x08, 0x8E);
    init_idt_entry(&idt[24], (u32)isr_no_err_24, 0x08, 0x8E);
    init_idt_entry(&idt[25], (u32)isr_no_err_25, 0x08, 0x8E);
    init_idt_entry(&idt[26], (u32)isr_no_err_26, 0x08, 0x8E);
    init_idt_entry(&idt[27], (u32)isr_no_err_27, 0x08, 0x8E);
    init_idt_entry(&idt[28], (u32)isr_no_err_28, 0x08, 0x8E);
    init_idt_entry(&idt[29], (u32)isr_no_err_29, 0x08, 0x8E);
    init_idt_entry(&idt[30], (u32)isr_no_err_30, 0x08, 0x8E);
    init_idt_entry(&idt[31], (u32)isr_no_err_31, 0x08, 0x8E);
    init_idt_entry(&idt[32], (u32)irq_0, 0x08, 0x8E);
    init_idt_entry(&idt[33], (u32)irq_1, 0x08, 0x8E);
    init_idt_entry(&idt[34], (u32)irq_2, 0x08, 0x8E);
    init_idt_entry(&idt[35], (u32)irq_3, 0x08, 0x8E);
    init_idt_entry(&idt[36], (u32)irq_4, 0x08, 0x8E);
    init_idt_entry(&idt[37], (u32)irq_5, 0x08, 0x8E);
    init_idt_entry(&idt[38], (u32)irq_6, 0x08, 0x8E);
    init_idt_entry(&idt[39], (u32)irq_7, 0x08, 0x8E);
    init_idt_entry(&idt[40], (u32)irq_8, 0x08, 0x8E);
    init_idt_entry(&idt[41], (u32)irq_9, 0x08, 0x8E);
    init_idt_entry(&idt[42], (u32)irq_10, 0x08, 0x8E);
    init_idt_entry(&idt[43], (u32)irq_11, 0x08, 0x8E);
    init_idt_entry(&idt[44], (u32)irq_12, 0x08, 0x8E);
    init_idt_entry(&idt[45], (u32)irq_13, 0x08, 0x8E);
    init_idt_entry(&idt[46], (u32)irq_14, 0x08, 0x8E);
    init_idt_entry(&idt[47], (u32)irq_15, 0x08, 0x8E);
    init_idt_entry(&idt[128], (u32)isr_no_err_128, 0x08, 0x8E);

    __asm__ volatile("lidt %0\n"
                     : /* no output */
                     : "m"(idtr)
                     : "memory");

    __asm__("sti\n");
}