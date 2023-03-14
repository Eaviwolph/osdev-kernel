#include <gdt/gdt.h>
#include <stdio.h>

static struct gdt gdt[6];
struct tss_entry tss;

void print_all_gdt()
{
    size_t i = 0;
    while (i < 6)
    {
        printf("GDT %u\r\n", i);
        printf("LIMIT: %x\r\n", gdt[i].limit_15_00);
        printf("BASE_1: %x\r\n", gdt[i].base_15_00);
        printf("BASE_2: %x\r\n", gdt[i].base_23_16);
        printf("ACCESS: %x\r\n", gdt[i].access);
        printf("LIMIT_FLAGS: %x\r\n", gdt[i].limit_19_16);
        printf("BASE_3: %x\r\n\r\n", gdt[i].base_31_24);

        i++;
    }
}

void init_gdt_entry(struct gdt *t, u32 base, u32 limit, u8 access,
                    u8 gran)
{
    t->base_15_00 = base & 0xFFFF; // First 16 bits
    t->base_23_16 = (base >> 16) & 0xFF; // Next 8 bits
    t->base_31_24 = (base >> 24 & 0xFF); // Last 8 bits

    t->access = access;

    // First 16 bits
    t->limit_15_00 = limit & 0xFFFF;
    // [ Last 4 bites of the granularity | First 4 bits of the last 16 bits ]
    t->limit_19_16 = (gran & 0xF0) | ((limit >> 16) & 0x0F);
}

void gdt_full_init(void)
{
    // The null segment
    init_gdt_entry(&gdt[0], 0, 0, 0, 0);
    // A kernel code segment
    init_gdt_entry(&gdt[1], 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // A kernel data segment
    init_gdt_entry(&gdt[2], 0, 0xFFFFFFFF, 0x92, 0xCF);
    // A userland code segment
    init_gdt_entry(&gdt[3], 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // A userland data segment
    init_gdt_entry(&gdt[4], 0, 0xFFFFFFFF, 0xF2, 0xCF);

    print_all_gdt();

    // stopping all interrupts
    __asm__ volatile("cli");

    // Loading gdtr
    struct gdtr gdtr;
    gdtr.base = (u32)gdt; /* gdt base address */
    gdtr.limit = sizeof(gdt) - 1; /* gdt size - 1 */
    asm volatile("lgdt %0\n"
                 : /* no output */
                 : "m"(gdtr)
                 : "memory");

    // Enable PE
    __asm__ volatile("mov %eax, %cr0\n"
                     "or %eax, 1\n"
                     "mov %cr0, %eax\n");

    // Kernel Data Segments = 0x10
    __asm__ volatile("movw $0x10, %ax\n"
                     "movw %ax, %ds\n"
                     "movw %ax, %es\n"
                     "movw %ax, %fs\n"
                     "movw %ax, %gs\n"
                     "movw %ax, %ss\n");

    // Switch: Code Data Segment = 0x08
    __asm__ volatile("ljmp $0x08, $1f\n"
                     "1:\n");
}

void tss_init(void)
{
    // A TSS to be able to switch from userland to kernelland.
    init_gdt_entry(&gdt[5], (u32)&tss, (u32)&tss + sizeof(struct tss_entry),
                   0x89, 0);

    tss.prev_tl = 0;
    tss.reserved0 = 0;
    tss.esp0 = 0;
    tss.ss0 = 0;
    tss.reserved1 = 0;
    tss.esp1 = 0;
    tss.ss1 = 0;
    tss.reserved2 = 0;
    tss.esp2 = 0;
    tss.ss2 = 0;
    tss.reserved3 = 0;
    tss.cr3 = 0;
    tss.eip = 0;
    tss.eflags = 0;
    tss.eax = 0;
    tss.ecx = 0;
    tss.edx = 0;
    tss.ebx = 0;
    tss.esp = 0;
    tss.ebp = 0;
    tss.esi = 0;
    tss.edi = 0;
    tss.es = 0x13;
    tss.reserved4 = 0;
    tss.cs = 0x0b;
    tss.reserved5 = 0;
    tss.ss = 0x13;
    tss.reserved6 = 0;
    tss.ds = 0x13;
    tss.reserved7 = 0;
    tss.fs = 0x13;
    tss.reserved8 = 0;
    tss.gs = 0x13;
    tss.reserved9 = 0;
    tss.ldt_seg = 0;
    tss.reserved10 = 0;
    tss.t = 0;
    tss.iomap_ba = 0;

    asm volatile("ltr %0\n"
                 : /* no output */
                 : "m"(tss)
                 : "memory");
}

void gdt_init(void)
{
    gdt_full_init();
    tss_init();
}