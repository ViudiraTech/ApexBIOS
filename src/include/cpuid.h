/*
 *      cpuid.h
 *      cpuid related operation header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_CPUID_H_
#define INCLUDE_CPUID_H_

#include "stdint.h"

#define CPUIDBrandVar 0x1060

/* Get CPUID */
void cpuid(uint32_t reg, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

/* Get CPU brand name */
char *cpu_get_brand(void);

/* Check if the CPU exists */
int cpu_detect(void);

/* Check whether the CPU supports 64-bit */
int cpu_is_64b(void);

#endif // INCLUDE_CPUID_H_
