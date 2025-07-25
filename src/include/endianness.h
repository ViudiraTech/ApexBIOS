/*
 *      endianness.h
 *      Byte order conversion related header files
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_ENDIANNESS_H_
#define INCLUDE_ENDIANNESS_H_

#include "stdint.h"

/* Swap the high 4 bits and low 4 bits of an 8-bit byte */
uint8_t swapendianness8(uint8_t byte);

/* Swap the upper and lower 8 bits of a 16-bit word */
uint16_t swapendianness16(uint16_t byte);

/* Swap the byte order of 32-bit words */
uint32_t swapendianness32(uint32_t byte);

/* Swap the byte order of 64-bit words */
uint64_t swapendianness64(uint64_t byte);

#endif // INCLUDE_ENDIANNESS_H_
