#pragma once

#include <k/kfs.h>
#include <k/types.h>

struct gdt
{
    u16 limit_15_00;
    u16 base_15_00;
    u8 base_23_16;
    u8 access;
    u8 limit_19_16;
    u8 base_31_24;
} __packed;

struct gdtr
{
    u16 limit;
    u32 base;
} __packed;

struct tss_entry
{
    u16 prev_tl;
    u16 reserved0;
    u32 esp0;
    u16 ss0;
    u16 reserved1;
    u32 esp1;
    u16 ss1;
    u16 reserved2;
    u32 esp2;
    u16 ss2;
    u16 reserved3;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u16 es;
    u16 reserved4;
    u16 cs;
    u16 reserved5;
    u16 ss;
    u16 reserved6;
    u16 ds;
    u16 reserved7;
    u16 fs;
    u16 reserved8;
    u16 gs;
    u16 reserved9;
    u16 ldt_seg;
    u16 reserved10;
    u16 t;
    u16 iomap_ba;
};

void gdt_init(void);