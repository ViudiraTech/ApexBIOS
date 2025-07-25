/*
 *      ports.h
 *      Computer port driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_PORTS_H_
#define INCLUDE_PORTS_H_

#include "stdint.h"

/* Read 8-bit data from the specified 16-bit port */
uint8_t inb(uint16_t port);

/* Read 16-bit data from the specified 16-bit port */
uint16_t inw(uint16_t port);

/* Read 32-bit data from the specified 16-bit port */
uint32_t inl(uint16_t port);

/* Write 8-bit data to the specified 16-bit port */
void outb(uint16_t port, uint8_t data);

/* Write 16-bit data to the specified 16-bit port */
void outw(uint16_t port, uint16_t data);

/* Write 32-bit data to the specified 16-bit port */
void outl(uint16_t port, uint32_t data);

#endif // INCLUDE_PORTS_H_
