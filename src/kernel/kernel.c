#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "util.h"

void main()
{
    isrInstall();
    __asm__ __volatile__("int $2");
    /* __asm__ __volatile__("int $3"); */
}

#endif
