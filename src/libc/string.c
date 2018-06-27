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

int strlen(char s[])
{
    int len = 0;
    while (s[len] != 0) ++len;
    return len;
}

void backspace(char s[])
{
    int len = strlen(s);
    if (len > 0) s[--len] = 0;
}

void append(char s[],char c)
{
    int len = strlen(s);
    s[len++] = c; s[len] = 0;
}

int strcmp(char s1[],char s2[])
{
    int i;
    for (int i = 0;;++i)
    {
	if (s1[i] != s2[i])
	    return s1[i] < s2[i]?-1:1;
	else if (s1[i] == 0) return 0;
    }
    return 0;
}

#endif
