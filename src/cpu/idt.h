#ifndef IDT_H
#define IDT_H

#include "types.h"

/* The code segment offset. */
const u32 KERNEL_CS = 0x08;
const int idtEntryNumber = 256;

struct IDTEntry
{
    u16 lowBase;		/* Low 16 bits of the handler's address. */
    u16 sel;			/* Kernel segment selector. */
    u8 always0;
    /*
      bit 7: "interrupt is present"
      bit 6-5: privilege level of caller(0 = kernel...3 = user)
      bit 4: set to 0 for interrupt gates
      bits 3-0:
     */
    u8 flags;
    u16 highBase; 
}__attribute__((packed));

struct IDTRegType
{
    u16 limit;
    u32 base;			/* The address of the first entry of idt. */
}__attribute__((packed));


IDTEntry idt[idtEntryNumber];
IDTRegType idtReg;

/* Some functions. */
void setIDTEntry(int n,u32 handler);
void setIDT();

#endif

