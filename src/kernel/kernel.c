#include "../drivers/ports.h"

void main()
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
    int offsetFromVGA = position<<1;
    char *vga = 0xb8000;
    vga[offsetFromVGA] = 'X';	/* The data. */
    vga[offsetFromVGA+1] = 0x0f; /* The color: white text on black background. */
}
