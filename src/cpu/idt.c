#ifndef IDT_C
#define IDT_C


#include "idt.h"

void setIDTEntry(int n,u32 handler)
{
    idt[n].lowBase = LOW16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8e;
    idt[n].highBase = HIGH16(handler);
}
void setIDT()
{
    idtReg.base = (u32)&idt;
    idtReg.limit = IDT_ENTRIES * sizeof(IDTEntry) - 1;
    __asm__ __volatile__("lidt (%0)": : "r" (&idtReg));
}

#endif
