#ifndef MEM_C
#define MEM_C

#include "mem.h"

void memoryCopy(char *source,char *dest,int nbytes)
{
    int i = 0;
    for (i = 0;i < nbytes;++i)
	*(dest+i) = *(source+i);
}

void memorySet(u8 *dest,u8 val,int len)
{
    u8 *now = dest;
    while (len--) *(now++) = val;
}

#endif
