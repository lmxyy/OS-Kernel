#ifndef MEM_H
#define MEM_H

#include "type.h"

void memoryCopy(char *source,char *dest,int nbytes);
void memorySet(uint8_t *dest,uint8_t val,int len);

uint32_t kmalloc(size_t size,int align,uint32_t *paddr);

#endif
