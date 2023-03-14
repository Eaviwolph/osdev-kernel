#include <stdio.h>

int test(int ebx, int ecx, int edx)
{
    (void)ebx;
    (void)ecx;
    (void)edx;
    printf("Test\r\n");
    return 0;
}
