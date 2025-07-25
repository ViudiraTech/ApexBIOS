/*
 *      eis.h
 *      Instruction set related header files
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_EIS_H_
#define INCLUDE_EIS_H_

#include "cpuid.h"
#include "ramfb.h"
#include "stdint.h"

/* Does FPU exist */
int fpu_detect(void);

/* FPU initialization */
void fpu_init(void);

/* Does the SSE instruction set exist */
int sse_detect(void);

/* SSE instruction set initialization */
void sse_init(void);

/* Does the AVX instruction set exist */
int avx_detect(void);

/* AVX instruction set initialization */
void avx_init(void);

#endif // INCLUDE_EIS_H_
