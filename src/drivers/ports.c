#ifndef PORTS_C
#define PORTS_C

#include "ports.h"

u8 portByteIn(u16 port)
{
    u8 ret;
    __asm__("in %%dx, %%al" : "=a"(ret) : "d"(port));
    return ret;
}

void portByteOut(u16 port,u8 data)
{
    __asm__ __volatile__("out %%al, %%dx" : : "d"(port),"a"(data));
}

u16 portWordIn(u16 port)
{
    u16 ret;
    __asm__("in %%dx, %%ax" : "=a"(ret) : "d"(port));
    return ret;
}

void portWordOut(u16 port,u16 data)
{
    __asm__ __volatile__("out %%ax, %%dx" : : "d"(port),"a"(data));
}

#endif
