#ifndef KERNEL_C
#define KERNEL_C

#include "../drivers/ports.h"
#include "../drivers/screen.h"

void main()
{
    clearScreen();
    kprintAt("X",6,1);
    kprintAt("This text spans multiple lines",10,75);
    kprintAt("There is a line\nbreak",20,0);
    kprint("There is a line\nbreak");
    kprintAt("What happens when we run out of space?",24,45);
}

#endif
