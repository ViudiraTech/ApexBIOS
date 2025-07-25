/*
 *      linker.ld
 *      Linker script written for BIOS format
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386:i386)

SECTIONS {
    . = 0xF0060;

    .text : {
        *(.text*)
    }
}
