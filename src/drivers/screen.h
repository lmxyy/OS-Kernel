#ifndef SCREEN_H
#define SCREEN_H

#include "../cpu/ports.h"
#define VIDEO_ADDRESS (0xb8000)
#define MAX_ROWS (25)
#define MAX_COLS (80)
#define WHITE_ON_BLACK (0x0f)
#define RED_ON_WHITE (0xf4)

#define REG_SCREEN_CTRL (0x3d4)
#define REG_SCREEN_DATA (0x3d5)

void clearScreen();
void kprintAt(char *message,int row,int col);
void kprint(char *message);
void kprintBackspace();

#endif
