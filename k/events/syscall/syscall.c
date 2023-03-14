#include <events/syscall.h>
#include <stdio.h>

int write_wrapper(int ebx, int ecx, int edx)
{
    (void)(edx);
    return write((char *)ebx, (size_t)ecx);
}

int getkey_wrapper(int ebx, int ecx, int edx)
{
    (void)(ebx);
    (void)(ecx);
    (void)(edx);
    return getkey();
}

int gettick_wrapper(int ebx, int ecx, int edx)
{
    (void)(ebx);
    (void)(ecx);
    (void)(edx);
    return gettick();
}

int setvideo_wrapper(int ebx, int ecx, int edx)
{
    (void)(ecx);
    (void)(edx);
    return setvideo(ebx);
}

int swap_frontbuffer_wrapper(int ebx, int ecx, int edx)
{
    (void)(ecx);
    (void)(edx);
    swap_frontbuffer((void *)ebx);
    return 0;
}

syscall *syscall_table[] = {test, write_wrapper, test, getkey_wrapper, gettick_wrapper, test, test, test, test, setvideo_wrapper, swap_frontbuffer_wrapper, test, test, test, test, NULL};
u32 size = 0;

void syscall_handler(registers_t *regs)
{
    if (regs->eax < size)
    {
        regs->eax = syscall_table[regs->eax](regs->ebx, regs->ecx, regs->edx);
        return;
    }
    regs->eax = -1;
}

void syscall_init(void)
{
    while (syscall_table[size] != NULL)
    {
        size++;
    }
    printf("Syscall table size: %d\n\r", size);
}