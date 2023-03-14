#pragma once

#include <events/idt.h>

extern void isr_no_err_0();
extern void isr_no_err_1();
extern void isr_no_err_2();
extern void isr_no_err_3();
extern void isr_no_err_4();
extern void isr_no_err_5();
extern void isr_no_err_6();
extern void isr_no_err_7();

extern void isr_err_8();

extern void isr_no_err_9();

extern void isr_err_10();
extern void isr_err_11();
extern void isr_err_12();
extern void isr_err_13();
extern void isr_err_14();

extern void isr_no_err_15();
extern void isr_no_err_16();
extern void isr_no_err_17();
extern void isr_no_err_18();
extern void isr_no_err_19();
extern void isr_no_err_20();
extern void isr_no_err_21();
extern void isr_no_err_22();
extern void isr_no_err_23();
extern void isr_no_err_24();
extern void isr_no_err_25();
extern void isr_no_err_26();
extern void isr_no_err_27();
extern void isr_no_err_28();
extern void isr_no_err_29();
extern void isr_no_err_30();
extern void isr_no_err_31();
extern void isr_no_err_128();

void isr_handler(registers_t *regs);