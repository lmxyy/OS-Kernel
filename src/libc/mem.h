#ifndef MEM_H
#define MEM_H

#include "../cpu/type.h"

void memoryCopy(char *source,char *dest,int nbytes);
void memorySet(u8 *dest,u8 val,int len);

u32 kmalloc(u32 size,int align,u32 *paddr);

#endif
