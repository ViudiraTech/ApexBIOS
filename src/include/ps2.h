/*
 *      ps2.h
 *      PS2 device driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_PS2_H_
#define INCLUDE_PS2_H_

#include "ports.h"
#include "ramfb.h"

#define PS2_DATA_PORT    0x60
#define PS2_STATUS_PORT  0x64
#define PS2_COMMAND_PORT 0x64

/* Wait for the output buffer of the PS/2 controller to be ready */
void PS2_wait_response(void);

/* Wait for the input buffer of the PS/2 controller to be ready */
void PS2_wait_input(void);

/* Perform self-test of the PS/2 controller */
uint8_t PS2_test(void);

/* Wait for the user to press a key and return the ASCII code of the key */
uint8_t PS2_wait_for_key(void);

/* Detect whether the PS/2 controller exists */
uint8_t PS2_detect(void);

/* Get the configuration byte of the PS/2 controller */
uint8_t PS2_get_config(void);

/* Set the configuration byte of the PS/2 controller */
void PS2_set_config(uint8_t cfg);

/* Initialize the PS/2 controller */
void PS2_init(void);

#endif // INCLUDE_PS2_H_
