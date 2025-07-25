/*
 *      cstring.c
 *      Basic string processing
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "cstring.h"

/* Calculate the length of a string */
int strlen(char *str)
{
    int i = 0;
    for (; str[i] != 0; i++);
    return i;
}

/* Comparing two strings */
int strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2++)
        if (*s1++ == 0) return 0;
    return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

/* Converts a 32-bit unsigned integer to a string */
int inttostr(uint32_t num)
{
    int k = 0, tmp = 0;

    do {
        tmp                        = num % 10;
        *((char *)Buffer1 + (k++)) = tmp + '0';
        num                        = num / 10;
    } while (num != 0);

    tmp = k;
    k   = 0;

    for (int i = tmp - 1; i >= 0; i--) { *((char *)Buffer2 + (k++)) = *((char *)Buffer1 + i); }
    *((char *)Buffer2 + tmp) = '\0';
    return Buffer2;
}

/* Convert a lowercase letter to uppercase */
char toupper(char chr)
{
    if (chr >= 'A' && chr <= 'Z') return chr + 32;
    return chr;
}
