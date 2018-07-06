#ifndef IDT_H
#define IDT_H

#include "../libc/type.h"

/* The code segment offset. */
#define KERNEL_CS (0x08)
#define IDT_ENTRIES (256)

typedef struct
{
    uint16_t lowBase;		/* Low 16 bits of the handler's address. */
    uint16_t selector;			/* Kernel segment selector. */
    uint8_t always0;
    /*
      bit 7: "interrupt is present"
      bit 6-5: privilege level of caller(0 = kernel...3 = user)
      bit 4: set to 0 for interrupt gates
      bits 3-0:
     */
    uint8_t flags;
    uint16_t highBase; 
}__attribute__((packed)) IDTEntry;

typedef struct
{
    uint16_t limit;
    uint32_t base;			/* The address of the first entry of idt. */
}__attribute__((packed)) IDTRegType;


IDTEntry idt[IDT_ENTRIES];
IDTRegType idtReg;

/* Some functions. */
void setIDTEntry(int n,uint32_t handler);
void setIDT();

#endif

