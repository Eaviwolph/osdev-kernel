#pragma once

#include <events/idt.h>
#include <drivers/keyboard.h>
#include <drivers/timer.h>
#include <drivers/serial.h>
#include <drivers/vga.h>
#include <k/types.h>

typedef int syscall(int ebx, int ecx, int edx);

void syscall_init(void);
void syscall_handler(registers_t *regs);

int test(int ebx, int ecx, int edx);
