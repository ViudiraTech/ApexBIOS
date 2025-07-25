/*
 *      cstring.h
 *      Basic string handling header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_CMOS_H_
#define INCLUDE_CMOS_H_

#include "memory.h"
#include "stdint.h"

#define Buffer1 0x1020
#define Buffer2 0x1040

/* Calculate the length of a string */
int strlen(char *str);

/* Comparing two strings */
int strcmp(const char *s1, const char *s2);

/* Converts a 32-bit unsigned integer to a string */
int inttostr(uint32_t num);

/* Convert a lowercase letter to uppercase */
char toupper(char chr);

#endif // INCLUDE_CMOS_H_
