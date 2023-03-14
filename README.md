# osdev-kernel
A kernel based on the legacy exercice of EPITA with the OSDev tutorial

## What has been done
### Serial driver
- [x] COM1 init
- [x] Write debug

### Memory manager
- [x] gdt
- [ ] tss
- [ ] malloc

### Events
- [x] interrupts (idt)
- [x] pic init

### Syscalls
- [x] Syscall handler
- [x] write
- [ ] sbrk (memory mapper)
- [x] getkey (keyboard input)
- [x] gettick (timer)
- [ ] open (file system)
- [ ] read (file system)
- [ ] seek (file system)
- [ ] close (file system)
- [x] setvideo (VGA mode)
- [x] swap_frontbuffer (VGA write buffer)
- [ ] playsound
- [ ] setpalette
- [ ] getmouse

### Binary loading
- [ ] ELF load

### Userland
- [ ] Memory swap
