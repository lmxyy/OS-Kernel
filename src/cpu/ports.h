#ifndef PORTS_H
#define PORTS_H

#include "../libc/type.h"

uint8_t portByteIn(uint16_t port);
void portByteOut(uint16_t port,uint8_t data);
uint16_t portWordIn(uint16_t port);
void portWordOut(uint16_t port,uint16_t data);

#endif
