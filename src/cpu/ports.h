#ifndef PORTS_H
#define PORTS_H

#include "type.h"

u8 portByteIn(u16 port);
void portByteOut(u16 port,u8 data);
u16 portWordIn(u16 port);
void portWordOut(u16 port,u16 data);

#endif
