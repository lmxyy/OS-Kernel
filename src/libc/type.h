#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>
#define LOW16(a) ((uint16_t)((a)&0xffff))
#define HIGH16(a) ((uint16_t)(((a)>>16)&0xffff))

#endif
