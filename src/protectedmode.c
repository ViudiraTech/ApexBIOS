/*
 *      protectedmode.c
 *      C language entry after protected mode
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "EPA.lib.h"
#include "ahci.h"
#include "atapio.h"
#include "bitmap.h"
#include "cpuid.h"
#include "eis.h"
#include "floppy.h"
#include "logo.lib.h"
#include "memory.h"
#include "pci.h"
#include "ps2.h"
#include "ramfb.h"
#include "serial.h"
#include "speaker.h"

/* BIOS protected mode entry */
extern void C_ENTRY(void)
{
    /* Initialize SSE instruction set */
    if (sse_detect()) sse_init();

    /* Initialize AVX instruction set */
    if (avx_detect()) avx_init();

    /* Initialize FPU */
    if (fpu_detect()) fpu_init();

    /* Initialize PIC */
    pic_init(0x08, 0x70);

    /* Initializing PS/2 */
    if (PS2_detect()) PS2_init();

    /* Initialize the floppy drive */
    if (floppy_get_drives()) floppy_init(FLOPPY_DRIVE_MASTER);

    /* Initialize RAMFB */
    RAMFB_init(640, 480);
    RAMFB_set_color(0xA8A8A8);

    /* ↓BIOS interface↓ */
    bmp_analysis((Bmp *)logo, 8, 11, 1);
    bmp_analysis((Bmp *)EPA, 480, 16, 1);

    RAMFB_put_str("\n         Apex Modular BIOS v0.01.\n");
    RAMFB_put_str("         Copyright (C) 2020 ViudiraTech.\n\n");

    RAMFB_put_str("Chipset: ");

    if (IS_Q35)
        RAMFB_put_str("Q35\n\n");
    else if (IS_I440FX)
        RAMFB_put_str("i440FX\n\n");
    else if (IS_MICROVM) {
        RAMFB_set_color(0xFF0000);
        RAMFB_put_str("MicroVM (Unsupported)\n\n");
        while (1) __asm__ volatile("hlt");
    } else {
        RAMFB_set_color(0xFF0000);
        RAMFB_put_str("Unknown\n\n");
        while (1) __asm__ volatile("hlt");
    }

    RAMFB_put_str("CPU: ");
    RAMFB_put_str(cpu_get_brand());
    RAMFB_put_str("\n");

    RAMFB_put_str("Memory: ");
    RAMFB_put_str(inttostr(ram_detect()));
    RAMFB_put_str("K\n\n");

    RAMFB_put_str("Detecting AHCI   ... ");
    if (ahci_detect_controller())
        RAMFB_put_str("AHCI Controller present.\n");
    else
        RAMFB_put_str("AHCI Controller Not present.\n");

    RAMFB_put_str("Detecting IDE    ... ");
    if (ata_controller_detect())
        RAMFB_put_str("IDE Controller present.\n");
    else
        RAMFB_put_str("IDE Controller Not present.\n");

    RAMFB_put_str("Detecting Floppy ... ");
    if (floppy_get_drives()) {
        RAMFB_put_str("Floppy Number: ");
        RAMFB_put_str(inttostr(floppy_get_drives()));
        RAMFB_put_str("\n\n");
    } else {
        RAMFB_put_str("Floppy Not present.\n\n");
    }

    /* Try to boot */
    if (ata_controller_detect() && ata_driver_detect()) {
        RAMFB_put_str("Booting from Hard Disk...\n");
        memset((void *)0x7C00, 0, 512);
        ata_read_lba(0, 0x7c00);
        if (*((uint16_t *)0x7dfe) == 0xAA55) {
            void (*boot)(void) = (void (*)(void))(0x7c00);
            boot();
        } else {
            RAMFB_put_str("Boot failed: not bootable disk.\n");
        }
    } else {
        RAMFB_put_str("No bootable device.\n");
    }

    while (1) { __asm__ volatile("hlt"); }
}
