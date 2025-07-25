/*
 *      cmos.c
 *      CMOS memory
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "cmos.h"
#include "ports.h"

/* Read CMOS memory */
uint8_t cmos_get_reg(uint16_t reg)
{
    outb(0x70, reg);
    return inb(0x71);
}

/* Get the current seconds */
uint8_t cmos_get_second(void)
{
    uint8_t val = cmos_get_reg(0x0);
    if (!(cmos_get_reg(0x0B) & 0x04)) val = bcdtobin(val);
    return val;
}

/* Get the current minute */
uint8_t cmos_get_minute(void)
{
    uint8_t val = cmos_get_reg(0x2);
    if (!(cmos_get_reg(0x0B) & 0x04)) val = bcdtobin(val);
    return val;
}

/* Get the current hour */
uint8_t cmos_get_hour(void)
{
    uint8_t val = cmos_get_reg(0x4);
    if (!(cmos_get_reg(0x0B) & 0x04)) val = bcdtobin(val);
    return val;
}

/* Get the current date */
uint8_t cmos_get_day(void)
{
    uint8_t val = cmos_get_reg(0x7);
    if (!(cmos_get_reg(0x0B) & 0x04)) val = bcdtobin(val);
    return val;
}

/* Get the current month */
uint8_t cmos_get_month(void)
{
    uint8_t val = cmos_get_reg(0x8);
    if (!(cmos_get_reg(0x0B) & 0x04)) val = bcdtobin(val);
    return val;
}

/* Get the current year */
uint8_t cmos_get_year(void)
{
    uint8_t val = cmos_get_reg(0x9);
    if (!(cmos_get_reg(0x0B) & 0x04)) val = bcdtobin(val);
    return val;
}
