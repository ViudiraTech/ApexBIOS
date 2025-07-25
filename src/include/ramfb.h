/*
 *      ramfb.h
 *      RAMFB-based graphics display driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_RAMFB_H_
#define INCLUDE_RAMFB_H_

#include "cstring.h"
#include "endianness.h"
#include "ports.h"
#include "serial.h"
#include "stddef.h"
#include "stdint.h"

#define FWCFG_DMA_PORT 0x518
#define FWCFG_ROOT     0x19

#define FWCFGCommand_ERROR  (1 << 0)
#define FWCFGCommand_READ   (1 << 1)
#define FWCFGCommand_SKIP   (1 << 2)
#define FWCFGCommand_SELECT (1 << 3)
#define FWCFGCommand_WRITE  (1 << 4)

#define VideoMemory 0x100000

#define CursorX     *((uint32_t *)0x1000)
#define CursorY     *((uint32_t *)0x1004)
#define ScreenW     *((uint32_t *)0x1008)
#define ScreenH     *((uint32_t *)0x100C)
#define Color       *((uint32_t *)0x1010)
#define FontScaling 2

struct FWCFGFile {
        uint32_t Size;
        uint16_t Selector;
        uint8_t  Offset[2];
        char     Name[56];
} __attribute__((packed));

struct FWCFGCommand {
        uint32_t Control;
        uint32_t Length;
        uint64_t Address;
} __attribute__((packed));

struct RAMFBStruct {
        uint64_t Address;
        uint32_t FOURCC;
        uint32_t Flags;
        uint32_t Width;
        uint32_t Height;
        uint32_t Stride;
} __attribute__((packed));

/* Find the information of the specified file in FWCFG */
int FWCFG_locate_file(char *filename, struct FWCFGFile *info);

/* Read data from FWCFG */
void FWCFG_read(uint16_t selector, void *buf, uint32_t len, uint32_t offset);

/* Write data to FWCFG */
void FWCFG_write(uint16_t selector, const void *buf, uint32_t len, uint32_t offset);

/* Draw a pixel at the specified location */
void RAMFB_put_pix(int x, int y, uint32_t clr);

/* Draw a filled rectangle */
void RAMFB_put_rectf(int x, int y, int w, int h, uint32_t clr);

/* Draw a hollow rectangle */
void RAMFB_put_rect(int x, int y, int w, int h, uint32_t clr);

/* Draw a character at the specified position */
void RAMFB_put_char(int x, int y, char chr);

/* Draw a string on the screen */
void RAMFB_put_str(char *str);

/* Set the drawing color */
void RAMFB_set_color(uint32_t color);

/* Set the cursor row position */
void RAMFB_set_rows(int rows);

/* Initialize RAMFB */
void RAMFB_init(int width, int height);

#endif // INCLUDE_RAMFB_H_
