/*
 *      memory.c
 *      Memory Management
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "memory.h"

/* Using CMOS registers to test system memory */
uint32_t ram_detect(void)
{
    uint32_t low  = (((uint16_t)cmos_get_reg(0x16) << 8) | cmos_get_reg(0x15));
    uint32_t ext  = (((uint16_t)cmos_get_reg(0x18) << 8) | cmos_get_reg(0x17));
    uint32_t xext = (((((uint16_t)cmos_get_reg(0x35) << 8) | cmos_get_reg(0x34)) * 65536) / 1024);

    if (xext == 0) {
        if (ext != 0 && ext > 1) return ext + 1024;
        __asm__ volatile("hlt");
    } else {
        return xext + 16384;
    }
}

/* Copying a memory area */
void *memcpy(void *dest, const void *src, uint32_t len)
{
    char       *d = dest;
    const char *s = src;
    while (len--) *d++ = *s++;
    return dest;
}

/* Set the value of a memory area */
void memset(void *dest, int val, uint32_t len)
{
    while (len-- > 0) *((uint8_t *)dest++) = val;
    return dest;
}
