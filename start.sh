#!/bin/sh

(make | make k.iso) && qemu-system-i386 -cdrom k.iso -serial stdio