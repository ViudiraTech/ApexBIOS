/*
 *      cmos.h
 *      CMOS memory header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_CMOS_H_
#define INCLUDE_CMOS_H_

#include "stdint.h"

#define bcdtobin(x) (x & 0x0F) + ((x / 16) * 10)

/* Read CMOS memory */
uint8_t cmos_get_reg(uint16_t reg);

/* Get the current seconds */
uint8_t cmos_get_second(void);

/* Get the current minute */
uint8_t cmos_get_minute(void);

/* Get the current hour */
uint8_t cmos_get_hour(void);

/* Get the current date */
uint8_t cmos_get_day(void);

/* Get the current month */
uint8_t cmos_get_month(void);

/* Get the current year */
uint8_t cmos_get_year(void);

#endif // INCLUDE_CMOS_H_
