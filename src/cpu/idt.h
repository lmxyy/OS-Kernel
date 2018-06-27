#ifndef IDT_H
#define IDT_H

#include "type.h"

/* The code segment offset. */
#define KERNEL_CS (0x08)
#define IDT_ENTRIES (256)

typedef struct
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
}__attribute__((packed)) IDTEntry;

typedef struct
{
    u16 limit;
    u32 base;			/* The address of the first entry of idt. */
}__attribute__((packed)) IDTRegType;


IDTEntry idt[IDT_ENTRIES];
IDTRegType idtReg;

/* Some functions. */
void setIDTEntry(int n,u32 handler);
void setIDT();

#endif

