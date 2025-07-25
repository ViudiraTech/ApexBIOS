/*
 *      serial.h
 *      RS-232 serial port driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_SERIAL_H_
#define INCLUDE_SERIAL_H_

#include "ports.h"

#define COM1 0x3F8

/* Sending a string through the serial port */
void serial_put_str(char *str);

/* Sending a single character over the serial port */
void serial_put_char(char ch);

#endif // INCLUDE_SERIAL_H_
