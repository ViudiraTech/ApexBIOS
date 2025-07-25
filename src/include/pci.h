/*
 *      pci.h
 *      PCI device driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_PCI_H_
#define INCLUDE_PCI_H_

#include "ports.h"
#include "stdint.h"

#define PCI_CFG_ADDRESS   0xCF8
#define PCI_CFG_VENDOR    0x00
#define PCI_CFG_DEVICE    0x02
#define PCI_CFG_INTERFACE 0x09
#define PCI_CFG_SUBCLASS  0x0A
#define PCI_CFG_CLASS     0x0B

typedef struct {
        uint16_t Vendor;
        uint16_t Device;
} PCIChipset;

#define Q35_VENDOR            0x8086
#define Q35_DEVICE            0x29C0
#define I440FX_VENDOR         0x8086
#define I440FX_DEVICE         0x1237
#define MICROVM_VENDOR_DEVICE 0xFFFF

#define IS_Q35     (PCI_get_chipset().Device == Q35_DEVICE && PCI_get_chipset().Vendor == Q35_VENDOR)
#define IS_I440FX  (PCI_get_chipset().Device == I440FX_DEVICE && PCI_get_chipset().Vendor == I440FX_VENDOR)
#define IS_MICROVM (PCI_get_chipset().Device == MICROVM_VENDOR_DEVICE && PCI_get_chipset().Vendor == MICROVM_VENDOR_DEVICE)

/* Read the 32-bit configuration register of the PCI device */
uint16_t PCI_read_dword(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);

/* Read the 16-bit configuration register of the PCI device */
uint16_t PCI_read_word(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);

/* Read the 8-bit configuration register of the PCI device */
uint16_t PCI_read_byte(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);

/* Write the 32-bit configuration register of the PCI device */
void PCI_write_dword(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint32_t data);

/* Write 16-bit configuration register of PCI device */
void PCI_write_word(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint16_t data);

/* Read 8-bit configuration register of PCI device */
void PCI_write_byte(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint8_t data);

/* Get the value of device base address register */
uint64_t PCI_get_bar(uint8_t bus, uint8_t slot, uint8_t function, int bar);

/* Get the vendor and device ID of PCI chipset */
PCIChipset PCI_get_chipset(void);

/* Find PCI device of specified class, subclass and programming interface */
uint8_t PCI_finl_device(uint8_t cls, uint8_t subcls, uint8_t programif);

/* Find PCI devices of the specified class and subclass, regardless of the programming interface */
uint8_t PCI_finl_deviceW(uint8_t cls, uint8_t subcls);

#endif // INCLUDE_PCI_H_
