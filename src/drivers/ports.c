/*
 *      ports.c
 *      Computer port driver
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "ports.h"

/* Read 8 bits of data from the specified 16-bit port */
uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile("in %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Read 16-bit data from the specified 16-bit port */
uint16_t inw(uint16_t port)
{
    uint16_t ret;
    __asm__ volatile("in %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Read 32-bit data from the specified 16-bit port */
uint32_t inl(uint16_t port)
{
    uint32_t ret;
    __asm__ volatile("in %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Write 8 bits of data to the specified 16-bit port */
void outb(uint16_t port, uint8_t data)
{
    __asm__ volatile("out %0, %1" ::"a"(data), "Nd"(port));
}

/* Write 16-bit data to the specified 16-bit port */
void outw(uint16_t port, uint16_t data)
{
    __asm__ volatile("out %0, %1" ::"a"(data), "Nd"(port));
}

/* Write 32-bit data to the specified 16-bit port */
void outl(uint16_t port, uint32_t data)
{
    __asm__ volatile("out %0, %1" ::"a"(data), "Nd"(port));
}
