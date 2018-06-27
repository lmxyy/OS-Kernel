#ifndef SCREEN_C
#define SCREEN_C

#include "../libc/mem.h"
#include "screen.h"

/* private functions */
int getCursorOffset()
{
    /* Query for the position of the cursor. */

    /* 14 is asking for the high byte of cursor position, the return signal is at the port 0x3d5. */
    portByteOut(0x3d4,14);
    int position = portByteIn(0x3d5);
    position = position<<8;

    /* 15 is asking for the low byte of cursor position, the return signal is at the port 0x3d5. */
    portByteOut(0x3d4,15);
    position += portByteIn(0x3d5);

    /* As every position contains the data and the background color. Every position is 2 bytes long. */
    return position<<1;
}

void setCursorOffset(int offset)
{
    offset >>= 1;
    portByteOut(REG_SCREEN_CTRL,14);
    portByteOut(REG_SCREEN_DATA,(unsigned char)(offset>>8));
    portByteOut(REG_SCREEN_CTRL,15);
    portByteOut(REG_SCREEN_DATA,(unsigned char)(offset&0xff));
}

int getOffset(int row,int col)
{
    return (row*MAX_COLS+col)<<1;
}

int getOffsetRow(int offset)
{
    return (offset>>1)/MAX_COLS;
}

int getOffsetCol(int offset)
{
    return (offset>>1)%MAX_COLS;
}

int printChar(char c,int row,int col,char attr)
{
    unsigned char *vidmen = (unsigned char*)VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;
    
    /* if the coordinates aren't right, print a red 'E'. */
    if (row >= MAX_ROWS||col >= MAX_COLS)
    {
	int screenSize = MAX_COLS*MAX_ROWS;
	vidmen[2*screenSize-2] = 'E';
	vidmen[2*screenSize-1] = RED_ON_WHITE;
	return getOffset(row,col);
    }

    int offset;
    if (row < 0||col < 0) offset = getCursorOffset();
    else offset = getOffset(row,col);

    if (c == '\n')
    {
	row = getOffsetRow(offset);
	offset = getOffset(row+1,0);
    }
    else
    {
	vidmen[offset] = c;
	vidmen[offset|1] = attr;
	offset += 2;
    }

    /* To scroll the screen. */
    if (offset >= ((MAX_ROWS*MAX_COLS)<<1))
    {
	int i;

	for (i = 0;i < MAX_ROWS-1;++i)
	    memoryCopy(VIDEO_ADDRESS+getOffset(i+1,0),VIDEO_ADDRESS+getOffset(i,0),MAX_COLS<<1);

	char *lastLine = VIDEO_ADDRESS+getOffset(MAX_ROWS-1,0);
	for (i = 0;i < (MAX_COLS<<1);++i) lastLine[i] = 0;

	offset -= (MAX_COLS<<1);
    }
    
    setCursorOffset(offset);
    return offset;
}

/* public functions */
void clearScreen()
{
    int screenSize = MAX_ROWS*MAX_COLS;
    unsigned char *vidmen = VIDEO_ADDRESS;
    
    int i = 0;
    for (i = 0;i < screenSize;++i)
    {
	vidmen[i<<1] = ' ';
	vidmen[i<<1|1] = WHITE_ON_BLACK;
    }
    setCursorOffset(getOffset(0,0));
}

void kprintAt(char *message,int row,int col)
{
    int offset;
    if (row < 0||col < 0)
    {
	offset = getCursorOffset();
	row = getOffsetRow(offset);
	col = getOffsetCol(offset);
    }
    else offset = getOffset(row,col);

    int i = 0;
    for (;message[i];++i)
    {
	offset = printChar(message[i],row,col,WHITE_ON_BLACK);
	row = getOffsetRow(offset);
	col = getOffsetCol(offset);
    }
}
void kprint(char *message)
{
    kprintAt(message,-1,-1);
}

#endif
