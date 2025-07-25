/*
 *      ps2.c
 *      PS2 Device Driver
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "ps2.h"

/* Waiting for the PS/2 controller's output buffer to be ready */
void PS2_wait_response(void)
{
    while (!(inb(PS2_STATUS_PORT) & 1));
}

/* Waiting for the PS/2 controller's input buffer to be ready */
void PS2_wait_input(void)
{
    while (inb(PS2_STATUS_PORT) & 2);
}

/* Perform a self-test on the PS/2 controller */
uint8_t PS2_test(void)
{
    outb(PS2_COMMAND_PORT, 0xAA);
    PS2_wait_response();
    return inb(PS2_DATA_PORT) == 0x55;
}

/* Wait for the user to press a key and return the ASCII code of the key */
uint8_t PS2_wait_for_key(void)
{
    const char ScanCodeSet1[] = {0,    0,   '1', '2',  '3', '4', '5', '6', '7',  '8', '9', '0', '-', '=', '\b', 0,   'q', 'w', 'e', 'r',
                                 't',  'y', 'u', 'i',  'o', 'p', '[', ']', '\n', 0,   'a', 's', 'd', 'f', 'g',  'h', 'j', 'k', 'l', ';',
                                 '\'', '`', 0,   '\\', 'z', 'x', 'c', 'v', 'b',  'n', 'm', ',', '.', '/', 0,    '*', 0,   ' '};
    while (1) {
        uint8_t c = inb(0x60);
        if (c > 0) return ScanCodeSet1[c];
    }
}

/* Detect if a PS/2 controller is present */
uint8_t PS2_detect(void)
{
    return PS2_test();
}

/* Get the configuration bytes of the PS/2 controller */
uint8_t PS2_get_config(void)
{
    PS2_wait_input();
    outb(PS2_COMMAND_PORT, 0x20);
    PS2_wait_response();
    return inb(0x60);
}

/* Set the configuration bytes of the PS/2 controller */
void PS2_set_config(uint8_t cfg)
{
    PS2_wait_input();
    outb(PS2_COMMAND_PORT, 0x60);
    PS2_wait_input();
    outb(0x60, cfg);
}

/* Initialize the PS/2 controller */
void PS2_init(void)
{
    outb(PS2_COMMAND_PORT, 0xAD);
    PS2_wait_input();

    outb(PS2_COMMAND_PORT, 0xA7);
    PS2_wait_input();

    inb(PS2_DATA_PORT);

    PS2_set_config(PS2_get_config() & ~1);
    PS2_set_config(PS2_get_config() & ~(1 << 1));

    PS2_set_config(PS2_get_config() & ~(1 << 6));

    PS2_test();

    outb(PS2_COMMAND_PORT, 0xAE);
    PS2_wait_input();

    outb(PS2_COMMAND_PORT, 0xA8);
    PS2_wait_input();

    PS2_set_config(PS2_get_config() | 1);
    PS2_set_config(PS2_get_config() | (1 << 1));

    PS2_set_config(PS2_get_config() | (1 << 6));

    outb(PS2_COMMAND_PORT, 0xFF);
    PS2_wait_input();

    outb(PS2_COMMAND_PORT, 0xD3);
    PS2_wait_input();
    outb(PS2_COMMAND_PORT, 0xFF);
    PS2_wait_input();
}
