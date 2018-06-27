#ifndef KERNEL_H
#define KERNEL_H

#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"

void userInput(char *input);

#endif
