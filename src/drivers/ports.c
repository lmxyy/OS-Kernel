#ifndef PORTS_C
#define PORTS_C

unsigned char portByteIn(unsigned short port)
{
    unsigned char ret;
    __asm__("in %%dx, %%al" : "=a"(ret) : "d"(port));
    return ret;
}

void portByteOut(unsigned short port,unsigned char data)
{
    __asm__("out %%al, %%dx" : : "d"(port),"a"(data));
}

unsigned char portWordIn(unsigned short port)
{
    unsigned char ret;
    __asm__("in %%dx, %%ax" : "=a"(ret) : "d"(port));
    return ret;
}

void portWordOut(unsigned short port,unsigned char data)
{
    __asm__("out %%ax, %%dx" : : "d"(port),"a"(data));
}

#endif
