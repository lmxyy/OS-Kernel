#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"

void main()
{
    isrInstall();
    irqInstall();
}

#endif
