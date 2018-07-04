#ifndef MEM_C
#define MEM_C

#include "mem.h"

void memoryCopy(char *source,char *dest,int nbytes)
{
    int i = 0;
    for (i = 0;i < nbytes;++i)
	*(dest+i) = *(source+i);
}

void memorySet(uint8_t *dest,uint8_t val,int len)
{
    uint8_t *now = dest;
    while (len--) *(now++) = val;
}

uint32_t freeAddr = 0x10000;
/* For paging, the address are aligned to 4K(0x1000). */
uint32_t kmalloc(size_t size,int align,uint32_t *paddr) // align is a flag to decide whether to align
{
    /* For aligning. */
    if (align == 1&&(freeAddr&0xfffff000))
    {
	freeAddr &= 0xfffff000;
	freeAddr += 0x1000;
    }

    if (paddr) *paddr = freeAddr;

    uint32_t ret = freeAddr;
    freeAddr += size;
    return ret;
}

#endif
