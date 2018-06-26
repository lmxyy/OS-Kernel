#ifndef ISR_C
#define ISR_C

#include "types.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"
#include "isr.h"


void isrInstall()
{
    setIDTEntry(0, (u32)isr0);
    setIDTEntry(1, (u32)isr1);
    setIDTEntry(2, (u32)isr2);
    setIDTEntry(3, (u32)isr3);
    setIDTEntry(4, (u32)isr4);
    setIDTEntry(5, (u32)isr5);
    setIDTEntry(6, (u32)isr6);
    setIDTEntry(7, (u32)isr7);
    setIDTEntry(8, (u32)isr8);
    setIDTEntry(9, (u32)isr9);
    setIDTEntry(10, (u32)isr10);
    setIDTEntry(11, (u32)isr11);
    setIDTEntry(12, (u32)isr12);
    setIDTEntry(13, (u32)isr13);
    setIDTEntry(14, (u32)isr14);
    setIDTEntry(15, (u32)isr15);
    setIDTEntry(16, (u32)isr16);
    setIDTEntry(17, (u32)isr17);
    setIDTEntry(18, (u32)isr18);
    setIDTEntry(19, (u32)isr19);
    setIDTEntry(20, (u32)isr20);
    setIDTEntry(21, (u32)isr21);
    setIDTEntry(22, (u32)isr22);
    setIDTEntry(23, (u32)isr23);
    setIDTEntry(24, (u32)isr24);
    setIDTEntry(25, (u32)isr25);
    setIDTEntry(26, (u32)isr26);
    setIDTEntry(27, (u32)isr27);
    setIDTEntry(28, (u32)isr28);
    setIDTEntry(29, (u32)isr29);
    setIDTEntry(30, (u32)isr30);
    setIDTEntry(31, (u32)isr31);
    setIDT();
}

char *exceptionMessage[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isrHandler(RegType r)
{
    kprint("receive interrupt: ");
    char s[10];
    int2Ascii(r.intNo,s);
    kprint(s); kprint('\n');
    kprint(exceptionMessage[r.intNo]); kprint('\n');
}

#endif
