/*
 *      atapio.h
 *      ATA input and output driver header files
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_ATAPIO_H_
#define INCLUDE_ATAPIO_H_

#include "memory.h"
#include "pci.h"
#include "ports.h"
#include <stdint.h>

#define ATA_MASTER 0x1F0
#define ATA_SLAVE  0x170

#define ATA_READ_SECTORS_COMMAND 0x20
#define ATA_BUFFER               0x1090

/* LBA read ATA device */
char *ata_read_lba(uint32_t lba, void *buffer);

/* Is ATA controller present */
int ata_controller_detect(void);

/* Does the ATA device exist */
int ata_driver_detect(void);

#endif // INCLUDE_ATAPIO_H_
