/*
 *      ahci.c
 *      ahci driver
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "ahci.h"

/* Is AHCI controller present */
uint8_t ahci_detect_controller(void)
{
    return PCI_finl_device(0x1, 0x6, 0x1);
}
