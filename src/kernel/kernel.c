#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "kernel.h"

static int isExit(char *input)
{
    if (strncmp(input,"EXIT",4) != 0)
	return 0;
    else return input[4] == 0||input[4] == ' ';
}

static int isPage(char *input)
{
    if (strncmp(input,"PAGE",4) != 0)
	return 0;
    else return input[4] == 0||input[4] == ' ';
}

void userInput(char *input)
{
    while (*input == ' ') input++;
    if (isExit(input))
    {
	kprint("Stopping the CPU. Bye!\n");
	asm volatile ("hlt");
    }
    else if (isPage(input))
    {
	uint32_t paddr; int size = ascii2Int(input+4);
	if (size <= 0) size = 1000;
	uint32_t page = kmalloc(size,1,&paddr);
	char pageStr[20],paddrStr[20];
	hex2Ascii(page,pageStr);
	hex2Ascii(paddr,paddrStr);
	kprint("Page: ");
	kprint(pageStr);
	kprint(", physical address: ");
	kprint(paddrStr);
	kprint("\n");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}

void kernelMain()
{
    isrInstall();
    irqInstall();
    kprint("\n> ");
}

#endif
