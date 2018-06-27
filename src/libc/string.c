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

void hex2Ascii(int n,char str[])
{
    int len = 0;
    str[len++] = '0'; str[len++] = 'x';

    int pzero = 0;
    s32 now; int i = 28;
    for (;i >= 0;i -= 4)
    {
	now = (n>>i)&0xf;
	if (i != 0&&now == 0&&!pzero) continue;
	pzero = 1;
	if (now >= 0xa) str[len++] = now-0xa+'a';
	else str[len++] = now+'0';
    }
    str[len] = 0;
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
    int i = 0;
    for (;;++i)
    {
	if (s1[i] != s2[i])
	    return s1[i] < s2[i]?-1:1;
	else if (s1[i] == 0) return 0;
    }
    return 0;
}

int strncmp(char s1[],char s2[],int n)
{
    int i = 0;
    for (;i < n;++i)
    {
	if (s1[i] != s2[i])
	    return s1[i] < s2[i]?-1:1;
	else if (s1[i] == 0) return 0;
    }
    return 0;
}

int ascii2Int(char *str)
{
    while (*str == ' ') ++str;
    int n = strlen(str);
    int f = 1,i = 0,ret = 0;
    if (str[0] == '-')
	f = -1,++i;
    for (;i < n;++i)
	ret = ret*10+(str[i]-'0');
    return ret*f;
}

#endif
