#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"

void main()
{
    isrInstall();
    /* __asm__ __volatile__("int $2"); */
    /* __asm__ __volatile__("int $3"); */
    __asm__ __volatile__("sti");
    initTimer(50);
    initKeyboard();
}

#endif
