#pragma once

#include <k/kfs.h>
#include <k/types.h>

#define IDT_ENTRIES_NUM 256

typedef struct registers
{
    u32 gs, fs, es, ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 int_no, err_code;
    u32 eip, cs, eflags, useresp, ss;
} registers_t;

struct idt
{
    u16 offset_15_0;
    u16 seg_selector;
    u8 gate_type;
    u8 flags;
    u16 offset_31_16;
} __packed;

struct idtr
{
    u16 limit;
    u32 base;
} __packed;

void idt_init();