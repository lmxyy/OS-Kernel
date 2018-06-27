#ifndef STRING_C
#define STRING_C

#include "string.h"

void int2Ascii(int n,char str[])
{
    int i = 0,j = 0,sign = 0;
    if (n < 0) sign = 1,n = -n;
    do str[i++] = n%10+'0',n /= 10;
    while (n);
    if (sign) str[i++] = '-';
    for (j = 0;j < (i-j-1);++j)
    {
	char c = str[j];
	str[j] = str[i-j-1];
	str[i-j-1] = c;
    }
}

#endif
