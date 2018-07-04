#ifndef PORTS_C
#define PORTS_C

#include "ports.h"

uint8_t portByteIn(uint16_t port)
{
    uint8_t ret;
    __asm__("in %%dx, %%al" : "=a"(ret) : "d"(port));
    return ret;
}

void portByteOut(uint16_t port,uint8_t data)
{
    __asm__ __volatile__("out %%al, %%dx" : : "d"(port),"a"(data));
}

uint16_t portWordIn(uint16_t port)
{
    uint16_t ret;
    __asm__("in %%dx, %%ax" : "=a"(ret) : "d"(port));
    return ret;
}

void portWordOut(uint16_t port,uint16_t data)
{
    __asm__ __volatile__("out %%ax, %%dx" : : "d"(port),"a"(data));
}

#endif
