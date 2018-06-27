#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void memoryCopy(char *source,char *dest,int nbytes);
void memorySet(u8 *dest,u8 val,int len);

#endif
