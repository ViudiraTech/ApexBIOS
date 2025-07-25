/*
 *      atapio.c
 *      ATA input and output driver
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "atapio.h"

/* LBA read ATA device */
char *ata_read_lba(uint32_t lba, void *buffer)
{
    outb(ATA_MASTER + 6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_MASTER + 1, 0);
    outb(ATA_MASTER + 2, 1);
    outb(ATA_MASTER + 3, lba);
    outb(ATA_MASTER + 4, lba >> 8);
    outb(ATA_MASTER + 5, lba >> 16);
    outb(ATA_MASTER + 7, ATA_READ_SECTORS_COMMAND);
    while (inb(ATA_MASTER + 7) & 128);

    for (int i = 0; i < 256; i++) { *((uint16_t *)ATA_BUFFER + i) = inw(ATA_MASTER); }
    memcpy(buffer, ATA_BUFFER, 512);
    return buffer;
}

/* Is ATA controller present */
int ata_controller_detect(void)
{
    return PCI_finl_deviceW(0x1, 0x1);
}

/* Does the ATA device exist */
int ata_driver_detect(void)
{
    if (inb(ATA_MASTER + 0x07) == 0)
        return 0;
    else
        return 1;
}
