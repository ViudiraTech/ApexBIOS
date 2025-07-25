/*
 *      bitmap.h
 *      Bitmap image parsing header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_BITMAP_H_
#define INCLUDE_BITMAP_H_

#include "stdint.h"

typedef struct {
        uint16_t magic;
        uint32_t fileSize;
        uint32_t reserved;
        uint32_t bmpDataOffset;
        uint32_t bmpInfoSize;
        uint32_t frameWidth;
        uint32_t frameHeight;
        uint16_t reservedValue;
        uint16_t bitsPerPixel;
        uint32_t compressionMode;
        uint32_t frameSize;
        uint32_t horizontalResolution;
        uint32_t verticalResolution;
        uint32_t usedColorCount;
        uint32_t importantColorCount;
} __attribute__((packed)) Bmp;

/* Parse BMP and display */
void bmp_analysis(Bmp *bmp, uint32_t x, uint32_t y, int isTransparent);

#endif // INCLUDE_BITMAP_H_
