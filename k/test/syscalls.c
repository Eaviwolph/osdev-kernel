#include "syscalls.h"

static inline u32 syscall0(int syscall_nb)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb));

	return res;
}

static inline u32 syscall1(int syscall_nb, u32 ebx)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb), "b"(ebx));

	return res;
}

static inline u32 syscall2(int syscall_nb, u32 ebx, u32 ecx)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb), "b"(ebx), "c"(ecx));

	return res;
}

static inline u32 syscall3(int syscall_nb, u32 ebx, u32 ecx, u32 edx)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb), "b"(ebx), "c"(ecx), "d"(edx));

	return res;
}

int writetest(const void *s, size_t length)
{
	return ((int)syscall2(SYSCALL_WRITE, (u32)s, length));
}

void *sbrktest(ssize_t increment)
{
	return ((void *)syscall1(SYSCALL_SBRK, increment));
}

int getkeytest(void)
{
	return ((int)syscall0(SYSCALL_GETKEY));
}

unsigned long getticktest(void)
{
	return ((unsigned long)syscall0(SYSCALL_GETTICK));
}

int opentest(const char *pathname, int flags)
{
	return ((int)syscall2(SYSCALL_OPEN, (u32)pathname, flags));
}

ssize_t readtest(int fd, void *buf, size_t count)
{
	return ((ssize_t)syscall3(SYSCALL_READ, fd, (u32)buf, count));
}

off_t lseektest(int filedes, off_t offset, int whence)
{
	return ((off_t)syscall3(SYSCALL_SEEK, filedes, offset, whence));
}

int closetest(int fd)
{
	return ((int)syscall1(SYSCALL_CLOSE, fd));
}

int playsoundtest(struct melody *melody, int repeat)
{
	return ((int)syscall2(SYSCALL_PLAYSOUND, (u32)melody, repeat));
}

int setvideotest(int mode)
{
	return ((int)syscall1(SYSCALL_SETVIDEO, mode));
}

void swap_frontbuffertest(const void *buffer)
{
	syscall1(SYSCALL_SWAP_FRONTBUFFER, (u32)buffer);
}

int getmousetest(int *x, int *y, int *buttons)
{
	return ((int)syscall3(SYSCALL_GETMOUSE, (u32)x, (u32)y, (u32)buttons));
}


void set_palettetest(unsigned int *new_palette, size_t size)
{
	syscall2(SYSCALL_SETPALETTE, (u32)new_palette, size);
}
