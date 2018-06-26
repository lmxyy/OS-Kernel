#ifndef ISR_C
#define ISR_C

#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../kernel/util.h"
#include "types.h"
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
    
    picRemap();

    setIDTEntry(32, (u32)irq0);
    setIDTEntry(33, (u32)irq1);
    setIDTEntry(34, (u32)irq2);
    setIDTEntry(35, (u32)irq3);
    setIDTEntry(36, (u32)irq4);
    setIDTEntry(37, (u32)irq5);
    setIDTEntry(38, (u32)irq6);
    setIDTEntry(39, (u32)irq7);
    setIDTEntry(40, (u32)irq8);
    setIDTEntry(41, (u32)irq9);
    setIDTEntry(42, (u32)irq10);
    setIDTEntry(43, (u32)irq11);
    setIDTEntry(44, (u32)irq12);
    setIDTEntry(45, (u32)irq13);
    setIDTEntry(46, (u32)irq14);
    setIDTEntry(47, (u32)irq15);
    
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

void regIntHandler(u8 n,ISRType handler)
{
    intHandlers[n] = handler;
}

void irqHandler(RegType r)
{
    /* send EOI first */
    if (r.intNo >= 40) // irq >= 8
	portByteOut(PIC2_COMMAND,PIC_EOI);
    portByteOut(PIC1_COMMAND,PIC_EOI);

    if (intHandlers[r.intNo] != NULL)
    {
	ISRType handler = intHandlers[r.intNo];
	handler(r);
    }
}

#endif
