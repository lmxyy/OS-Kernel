#ifndef TYPES_H
#define TYPES_H

typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

#define LOW16(a) ((u16)((a)&0xffff))
#define HIGH16(a) ((u16)(((a)>>16)&0xffff))

#endif
