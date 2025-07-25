/*
 *      memory.h
 *      Memory management header files
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include "cmos.h"
#include "serial.h"
#include "speaker.h"
#include "stdint.h"

/* Use CMOS registers to detect system memory */
uint32_t ram_detect(void);

/* Copy memory area */
void *memcpy(void *dest, const void *src, uint32_t len);

/* Set the value of the memory area */
void memset(void *dest, int val, uint32_t len);

#endif // INCLUDE_MEMORY_H_
