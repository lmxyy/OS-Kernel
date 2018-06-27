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

u32 freeAddr = 0x10000;
/* For paging, the address are aligned to 4K(0x1000). */
u32 kmalloc(u32 size,int align,u32 *paddr) // align is a flag to decide whether to align
{
    /* For aligning. */
    if (align == 1&&(freeAddr&0xfffff000))
    {
	kprint("laalal");
	freeAddr &= 0xfffff000;
	freeAddr += 0x1000;
    }

    if (paddr) *paddr = freeAddr;

    u32 ret = freeAddr;
    freeAddr += size;
    return ret;
}

#endif
