#ifndef TIMER_C
#define TIMER_C

#include "../kernel/util.h"
#include "../drivers/screen.h"
#include "types.h"
#include "timer.h"
#include "isr.h"

static u32 tick = 0;

static void timerCallback(RegType reg)
{
    tick++;
    /* kprint("Tick: "); */

    /* char tickAscii[256]; */
    /* int2Ascii(tick,tickAscii); */
    /* kprint(tickAscii); kprint("\n"); */
}

void initTimer(u32 freq)
{
    regIntHandler(IRQ0,timerCallback);

    u32 divisor = 1193180/freq;
    u8 low = (u8)(divisor&0xff);
    u8 high = (u8)((divisor>>8)&0xff);

    portByteOut(0x43,0x36);
    portByteOut(0x40,low);
    portByteOut(0x40,high);
}

#endif
