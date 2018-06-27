#ifndef STRING_H
#define STRING_H

#include "../cpu/type.h"

void int2Ascii(int n,char str[]);
void hex2Ascii(int n,char str[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[],char c);
int strcmp(char s1[],char s2[]);
int strncmp(char s1[],char s2[],int n);
int ascii2Int(char *str);

#endif
