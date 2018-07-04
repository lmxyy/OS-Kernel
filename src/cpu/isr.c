#ifndef ISR_C
#define ISR_C

#include "../drivers/screen.h"
#include "../libc/string.h"
#include "ports.h"
#include "isr.h"
#include "idt.h"

ISRType intHandlers[IDT_ENTRIES];

void picRemap()
{
    /* PIC maps IRQs 0-7 to INT 0x8-0xF and IRQs 8-15 to INT 0x70-0x77 */
    portByteOut(PIC1_COMMAND, 0x11);	// starts the initialization sequence (in cascade mode) 
    portByteOut(PIC2_COMMAND, 0x11);
    portByteOut(PIC1_DATA, 0x20);
    portByteOut(PIC2_DATA, 0x28);
    portByteOut(PIC1_DATA, 0x04);
    portByteOut(PIC2_DATA, 0x02);
    portByteOut(PIC1_DATA, 0x01);
    portByteOut(PIC2_DATA, 0x01);
    portByteOut(PIC1_DATA, 0x0);
    portByteOut(PIC2_DATA, 0x0); 
}

void isrInstall()
{
    setIDTEntry(0, (uint32_t)isr0);
    setIDTEntry(1, (uint32_t)isr1);
    setIDTEntry(2, (uint32_t)isr2);
    setIDTEntry(3, (uint32_t)isr3);
    setIDTEntry(4, (uint32_t)isr4);
    setIDTEntry(5, (uint32_t)isr5);
    setIDTEntry(6, (uint32_t)isr6);
    setIDTEntry(7, (uint32_t)isr7);
    setIDTEntry(8, (uint32_t)isr8);
    setIDTEntry(9, (uint32_t)isr9);
    setIDTEntry(10, (uint32_t)isr10);
    setIDTEntry(11, (uint32_t)isr11);
    setIDTEntry(12, (uint32_t)isr12);
    setIDTEntry(13, (uint32_t)isr13);
    setIDTEntry(14, (uint32_t)isr14);
    setIDTEntry(15, (uint32_t)isr15);
    setIDTEntry(16, (uint32_t)isr16);
    setIDTEntry(17, (uint32_t)isr17);
    setIDTEntry(18, (uint32_t)isr18);
    setIDTEntry(19, (uint32_t)isr19);
    setIDTEntry(20, (uint32_t)isr20);
    setIDTEntry(21, (uint32_t)isr21);
    setIDTEntry(22, (uint32_t)isr22);
    setIDTEntry(23, (uint32_t)isr23);
    setIDTEntry(24, (uint32_t)isr24);
    setIDTEntry(25, (uint32_t)isr25);
    setIDTEntry(26, (uint32_t)isr26);
    setIDTEntry(27, (uint32_t)isr27);
    setIDTEntry(28, (uint32_t)isr28);
    setIDTEntry(29, (uint32_t)isr29);
    setIDTEntry(30, (uint32_t)isr30);
    setIDTEntry(31, (uint32_t)isr31);
    
    picRemap();

    setIDTEntry(32, (uint32_t)irq0);
    setIDTEntry(33, (uint32_t)irq1);
    setIDTEntry(34, (uint32_t)irq2);
    setIDTEntry(35, (uint32_t)irq3);
    setIDTEntry(36, (uint32_t)irq4);
    setIDTEntry(37, (uint32_t)irq5);
    setIDTEntry(38, (uint32_t)irq6);
    setIDTEntry(39, (uint32_t)irq7);
    setIDTEntry(40, (uint32_t)irq8);
    setIDTEntry(41, (uint32_t)irq9);
    setIDTEntry(42, (uint32_t)irq10);
    setIDTEntry(43, (uint32_t)irq11);
    setIDTEntry(44, (uint32_t)irq12);
    setIDTEntry(45, (uint32_t)irq13);
    setIDTEntry(46, (uint32_t)irq14);
    setIDTEntry(47, (uint32_t)irq15);
    
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
    kprint(s); kprint("\n");
    kprint(exceptionMessage[r.intNo]); kprint("\n");
}

void regIntHandler(uint8_t n,ISRType handler)
{
    intHandlers[n] = handler;
}

void irqHandler(RegType r)
{
    /* send EOI first */
    if (r.intNo >= 40) // irq >= 8
	portByteOut(PIC2_COMMAND,PIC_EOI);
    portByteOut(PIC1_COMMAND,PIC_EOI);

    if (intHandlers[r.intNo] != 0)
    {
	ISRType handler = intHandlers[r.intNo];
	handler(r);
    }
}

void irqInstall()
{
    __asm__ __volatile__ ("sti");
    initTimer(50);
    initKeyboard();
}

#endif
