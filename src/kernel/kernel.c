#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "util.h"

void main()
{
    isrInstall();
    /* __asm__ __volatile__("int $2"); */
    /* __asm__ __volatile__("int $3"); */
    __asm__ __volatile__("sti");
    initTimer(50);
}

#endif
