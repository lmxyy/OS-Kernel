#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "kernel.h"

void userInput(char *input)
{
    if (strcmp(input,"EXIT") == 0)
    {
	kprint("Stopping the CPU. Bye!\n");
	__asm__ __volatile__ ("hlt");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}

void main()
{
    isrInstall();
    irqInstall();
    kprint("\n> ");
}

#endif
