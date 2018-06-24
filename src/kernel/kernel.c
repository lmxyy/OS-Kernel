#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "util.h"

void main()
{
    clearScreen();
    /* kprintAt("X",6,1); */
    /* kprintAt("This text spans multiple lines",10,75); */
    /* kprintAt("There is a line\nbreak",20,0); */
    /* kprint("There is a line\nbreak"); */
    /* kprintAt("What happens when we run out of space?",24,45); */
    int i = 0;
    for (;i < 24;++i)
    {
	char str[255];
	int2Ascii(-i,str);
	kprintAt(str,i,0);
    }
    kprintAt("This text forces the kernel to scroll. Row 0 will disappear.",24,60);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");
}

#endif
