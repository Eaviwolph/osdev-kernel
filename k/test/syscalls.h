#pragma once

#include <k/kstd.h>

int writetest(const void *s, size_t length);
void *sbrktest(ssize_t increment);
int getkeytest(void);
unsigned long getticktest(void);
int opentest(const char *pathname, int flags);
ssize_t readtest(int fd, void *buf, size_t count);
off_t lseektest(int filedes, off_t offset, int whence);
int closetest(int fd);
int setvideotest(int mode);
void swap_frontbuffertest(const void *buffer);
int playsoundtest(struct melody *melody, int repeat);
int getmousetest(int *x, int *y, int *buttons);
int getkeymodetest(int mode);
