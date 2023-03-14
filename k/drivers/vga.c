#include "../libvga.h"
#include <drivers/vga.h>
#include <k/compiler.h>
#include <stdio.h>

int setvideo(int mode)
{
    if (mode == VIDEO_GRAPHIC)
    {
        libvga_switch_mode13h();
        return 0;
    }
    else if (mode == VIDEO_TEXT)
    {
        libvga_switch_mode3h();
        return 0;
    }
    return -1;
}

void swap_frontbuffer(const void *buffer)
{
    char *framebuffer = libvga_get_framebuffer();
    if (framebuffer == NULL || framebuffer == 0)
    {
        printf("framebuffer is NULL\n\r");
        return;
    }
    for (size_t i = 0; (int)(framebuffer + i) < 0xBFFFF; i++)
    {
        framebuffer[i] = ((char *)buffer)[i];
    }
}