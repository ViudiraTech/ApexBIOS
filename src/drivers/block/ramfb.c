/*
 *      ramfb.c
 *      Graphics display driver based on RAMFB
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "ramfb.h"
#include "bmpfont.h"
#include "speaker.h"

/* Find information about a specified file in FWCFG */
int FWCFG_locate_file(char *filename, struct FWCFGFile *info)
{
    uint32_t items;
    uint32_t offset = 0;
    FWCFG_read(FWCFG_ROOT, &items, sizeof(uint32_t), offset);
    offset += sizeof(uint32_t);
    items = swapendianness32(items);
    for (; offset < items * sizeof(struct FWCFGFile); offset += sizeof(struct FWCFGFile)) {
        struct FWCFGFile file;
        FWCFG_read(FWCFG_ROOT, &file, sizeof(struct FWCFGFile), offset);
        if (!strcmp(file.Name, filename)) {
            info->Selector = swapendianness16(file.Selector);
            info->Size     = swapendianness32(file.Size);
            memcpy(&info->Name, file.Name, 56);
            return 0;
        }
    }
    return -1;
}

/* Reading data from FWCFG */
void FWCFG_read(uint16_t selector, void *buf, uint32_t len, uint32_t offset)
{
    volatile struct FWCFGCommand command;
    command.Control = swapendianness32(((uint32_t)selector << 16) | FWCFGCommand_SKIP | FWCFGCommand_SELECT);
    command.Length  = swapendianness32(offset);
    outl(FWCFG_DMA_PORT, swapendianness32((uint32_t)&command));
    while (command.Control & ~FWCFGCommand_ERROR);
    command.Control = swapendianness32(((uint32_t)selector << 16) | FWCFGCommand_READ);
    command.Length  = swapendianness32(len);
    command.Address = swapendianness64((uint64_t)buf);
    outl(FWCFG_DMA_PORT, swapendianness32((uint32_t)&command));
    while (command.Control & ~FWCFGCommand_ERROR);
}

/* Write data to FWCFG */
void FWCFG_write(uint16_t selector, const void *buf, uint32_t len, uint32_t offset)
{
    volatile struct FWCFGCommand command;
    command.Control = swapendianness32(((uint32_t)selector << 16) | FWCFGCommand_SKIP | FWCFGCommand_SELECT);
    command.Length  = swapendianness32(offset);
    outl(FWCFG_DMA_PORT, swapendianness32((uint32_t)&command));
    while (command.Control & ~FWCFGCommand_ERROR);
    command.Control = swapendianness32(((uint32_t)selector << 16) | FWCFGCommand_WRITE);
    command.Length  = swapendianness32(len);
    command.Address = swapendianness64((uint64_t)buf);
    outl(FWCFG_DMA_PORT, swapendianness32((uint32_t)&command));
    while (command.Control & ~FWCFGCommand_ERROR);
}

/* Draws a pixel at the specified location */
void RAMFB_put_pix(int x, int y, uint32_t clr)
{
    *(uint32_t *)(x * 4 + (ScreenW * y * 4) + VideoMemory) = clr;
}

/* Draw a filled rectangle */
void RAMFB_put_rectf(int x, int y, int w, int h, uint32_t clr)
{
    for (int i = x; i < (x + w); i++)
        for (int j = y; j < (y + h); j++) RAMFB_put_pix(i, j, clr);
}

/* Draw a hollow rectangle */
void RAMFB_put_rect(int x, int y, int w, int h, uint32_t clr)
{
    RAMFB_put_rectf(x, y, w, 1, clr);
    RAMFB_put_rectf(x, y + h, w, 1, clr);
    RAMFB_put_rectf(x, y, 1, h, clr);
    RAMFB_put_rectf(x + w, y, 1, h, clr);
}

/* Draw a character at the specified position */
void RAMFB_put_char(int x, int y, char chr)
{
    uint32_t *screen = VideoMemory;
    uint8_t  *font   = BitmapFont;
    font += chr * 16;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 9; j++) {
            if (font[i] & (0x80 >> j)) screen[(y + i) * 640 + x + j] = Color;
        }
    }
}

/* Draw a string on the screen */
void RAMFB_put_str(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (CursorX + 4 * FontScaling >= ScreenW) {
            CursorY += 8 * FontScaling;
            CursorX = 0;
        }
        if (str[i] == '\n') {
            CursorY += 8 * FontScaling;
            CursorX = 1;
        } else {
            RAMFB_put_char(CursorX, CursorY, str[i]);
            CursorX += 4 * FontScaling;
        }
    }
}

/* Set the drawing color */
void RAMFB_set_color(uint32_t color)
{
    Color = color;
}

/* Set the cursor line position */
void RAMFB_set_rows(int rows)
{
    if (rows > 30 || rows < 1) return;
    CursorY = (rows * (8 * FontScaling)) - (8 * FontScaling);
}

/* Initialize RAMFB */
void RAMFB_init(int width, int height)
{
    struct FWCFGFile file;
    FWCFG_locate_file("etc/ramfb", &file);
    if (file.Selector) {
        struct RAMFBStruct RAMFB = {0};
        RAMFB.Width              = swapendianness32(width);
        RAMFB.Height             = swapendianness32(height);
        RAMFB.Stride             = swapendianness32(width * (32 / 8));
        RAMFB.Address            = swapendianness64(VideoMemory);
        RAMFB.FOURCC             = swapendianness32(0x34325241);
        FWCFG_write(file.Selector, &RAMFB, sizeof(RAMFB), 0);

        CursorX = 0;
        CursorY = 0;
        ScreenW = width;
        ScreenH = height;
        Color   = 0xFFFFFF;

        memset(VideoMemory, 0, (width * height) * (32 / 8));
    } else {
        __asm__ volatile("hlt");
    }
}
