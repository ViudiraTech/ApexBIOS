/*
 *      floppy.h
 *      Floppy disk driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_FLOPPY_H_
#define INCLUDE_FLOPPY_H_

#include "cmos.h"
#include "ramfb.h"
#include "stdint.h"

#define FLOPPY_BASE_PORT 0x3F0

#define FLOPPY_DOR_REG  2
#define FLOPPY_MSR_REG  4
#define FLOPPY_FIFO_REG 5
#define FLOPPY_CCR_REG  7

#define FLOPPY_SPECIFY_COMMAND     3
#define FLOPPY_WRITE_COMMAND       5
#define FLOPPY_READ_COMMAND        6
#define FLOPPY_RECALIBRATE_COMMAND 7
#define FLOPPY_SENSE_COMMAND       8
#define FLOPPY_SEEK_COMMAND        15

#define FLOPPY_DRIVE_MASTER 0
#define FLOPPY_DRIVE_SLAVE  1

#define FLOPPY_DMA_WRITE   0x4A
#define FLOPPY_DMA_READ    0x46
#define FLOPPY_DMA_LEN     0x4800
#define FLOPPY_DMA_ADDRESS 0x8000

/* Get the number of floppy drives in the system */
uint8_t floppy_get_drives(void);

/* Send a command to the floppy disk controller */
void floppy_do_command(uint8_t command);

/* Read a byte of data from the floppy disk controller's data register */
uint8_t floppy_read_fifo(void);

/* Handling floppy drive interrupts */
void floppy_sense_intrerrupt(uint8_t *cylinler, uint8_t *status);

/* Start the floppy drive motor */
void floppy_start_motor(void);

/* Stop the floppy drive motor */
void floppy_stop_motor(void);

/* Calibrate the specified floppy drive */
void floppy_calibrate(uint8_t drive);

/* Clear the interrupt queue of the floppy controller */
void floppy_flush_intrerrupt(void);

/* Initialize the floppy drive */
void floppy_init(uint8_t drive);

/* Move the floppy head to the specified cylinder and head position */
void floppy_seek(uint16_t cylinler, uint16_t head);

#endif // INCLUDE_FLOPPY_H_
