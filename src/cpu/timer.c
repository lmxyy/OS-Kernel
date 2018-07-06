#ifndef TIMER_C
#define TIMER_C

#include "../libc/string.h"
#include "../drivers/screen.h"
#include "timer.h"
#include "isr.h"

static uint32_t tick = 0;

static void timerCallback(RegType *reg) { tick++; }

void initTimer(uint32_t freq)
{
    regIntHandler(IRQ0,timerCallback);

    uint32_t divisor = 1193180/freq;
    uint8_t low = (uint8_t)(divisor&0xff);
    uint8_t high = (uint8_t)((divisor>>8)&0xff);

    portByteOut(0x43,0x36);
    portByteOut(0x40,low);
    portByteOut(0x40,high);
}

#endif
