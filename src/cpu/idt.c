#ifndef IDT_C
#define IDT_C

#include "idt.h"

void setIDTEntry(int n,uint32_t handler)
{
    idt[n].lowBase = LOW16(handler);
    idt[n].selector = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8e;
    idt[n].highBase = HIGH16(handler);
}
void setIDT()
{
    idtReg.base = (uint32_t)&idt;
    idtReg.limit = IDT_ENTRIES * sizeof(IDTEntry) - 1;
    asm volatile("lidt (%0)": : "r" (&idtReg));
}

#endif
