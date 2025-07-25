/*
 *      endianness.c
 *      Byte order conversion related
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "endianness.h"

/* Swap the high 4 bits and low 4 bits of an 8-bit byte */
uint8_t swapendianness8(uint8_t byte)
{
    return (byte >> 4) | (byte << 4);
}

/* Swap the upper and lower 8 bits of a 16-bit word */
uint16_t swapendianness16(uint16_t byte)
{
    return (byte >> 8) | (byte << 8);
}

/* Swap the byte order of 32-bit words */
uint32_t swapendianness32(uint32_t byte)
{
    return ((byte >> 8) & 0x0000FF00) | ((byte >> 24) & 0x000000FF) | ((byte << 24) & 0xFF000000) | ((byte << 8) & 0x00FF0000);
}

/* Swap the byte order of 64-bit words */
uint64_t swapendianness64(uint64_t byte)
{
    return ((uint64_t)swapendianness32(byte & 0xFFFFFFFF) << 32) | swapendianness32((byte >> 32) & 0xFFFFFFFF);
}
