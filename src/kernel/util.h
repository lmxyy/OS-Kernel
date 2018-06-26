#ifndef UTIL_H
#define UTIL_H

#include "../cpu/type.h"

void memoryCopy(char *source,char *dest,int nbytes);
void memorySet(u8 dest,u8 val,int len);
void int2Ascii(int n,char str[]);

#endif
