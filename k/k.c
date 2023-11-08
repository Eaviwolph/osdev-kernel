/*
 * Copyright (c) LSE
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LSE AS IS AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL LSE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <drivers/pic.h>
#include <drivers/serial.h>
#include <drivers/timer.h>
#include <drivers/keyboard.h>
#include <drivers/vga.h>
#include <drivers/atapi.h>
#include <events/idt.h>
#include <events/syscall.h>
#include <gdt/gdt.h>
#include <k/kstd.h>
#include <stdio.h>

#include "multiboot.h"
#include "test/syscalls.h"

void k_main(unsigned long magic, multiboot_info_t *info)
{
    (void)magic;
    (void)info;

    serial_init();
    printf("Hello World\r\n");

    gdt_init();
    pic_init();
    idt_init();
    keyboard_init();
    timer_init();
    syscall_init();

    // After this point, the code is used to test the kernel
    writetest("Hello World\r\n", 13);

    // char star[4] = "|/-\\";
    // char *fb = (void *)0xB8000; // VIDEO_GRAPHIC=0xA0000 VIDEO_TEXT=0xB8000;

    discover_atapi_drive();

    char buffer[80 * 25 * 2];
    for (unsigned i = 0; i < 80 * 25 * 2; i++)
    {
        if (i % 2 == 0)
            buffer[i] = '|';
        else
            buffer[i] = 0x0F;
    }
    buffer[80 * 25 * 2 - 2] = 'E';

    setvideotest(VIDEO_TEXT);
    swap_frontbuffertest(buffer);

    for (;;)
    {
        //*fb = star[i++ % 4];
        // char c = getkeytest();
        // if (c == -1)
        //     continue;
        // printf("%d\r\n", getticktest());
        //*fb = 'A';
    }

    for (;;)
        asm volatile("hlt");
}
