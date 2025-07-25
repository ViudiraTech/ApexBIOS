/*
 *      ahci.h
 *      ahci driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_AHCI_H_
#define INCLUDE_AHCI_H_

#include "stdint.h"

/* Is AHCI controller present */
uint8_t ahci_detect_controller(void);

#endif // INCLUDE_AHCI_H_
