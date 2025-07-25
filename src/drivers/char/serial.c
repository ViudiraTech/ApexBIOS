/*
 *      serial.c
 *      RS-232 serial port driver
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "serial.h"

/* Sending a string through the serial port */
void serial_put_str(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') serial_put_char('\r');
        serial_put_char(str[i]);
    }
}

/* Sending a single character over the serial port */
void serial_put_char(char ch)
{
    outb(COM1, ch);
}
