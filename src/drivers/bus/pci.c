/*
 *      pci.c
 *      PCI device drivers
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "pci.h"

/* Read the 32-bit configuration register of a PCI device */
uint16_t PCI_read_dword(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset)
{
    outl(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));
    return inw(0xCFC);
}

/* Read the 16-bit configuration register of the PCI device */
uint16_t PCI_read_word(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset)
{
    outl(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));
    return inw(0xCFC + (offset & 2));
}

/* Read the 8-bit configuration register of the PCI device */
uint16_t PCI_read_byte(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset)
{
    outl(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));
    return inb(0xCFC + (offset & 3));
}

/* Write to the 32-bit configuration register of the PCI device */
void PCI_write_dword(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint32_t data)
{
    outl(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));
    outl(0xCFC, data);
}

/* Write to the 16-bit configuration register of the PCI device */
void PCI_write_word(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint16_t data)
{
    outl(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));
    outw(0xCFC + (offset & 2), data);
}

/* Read the 8-bit configuration register of the PCI device */
void PCI_write_byte(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset, uint8_t data)
{
    outl(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));
    outb(0xCFC + (offset & 3), data);
}

/* Get the device base address register value */
uint64_t PCI_get_bar(uint8_t bus, uint8_t slot, uint8_t function, int bar)
{
    uint32_t bar_val = PCI_read_dword(bus, slot, function, 0x10 + (bar * 4));
    if (bar_val & 1) { return (uint64_t)((uint16_t)bar_val & ~0x03); }
    if (((bar_val >> 1) & 0x03) == 0) { return (uint64_t)(bar_val & ~0x0f); }
    if (((bar_val >> 1) & 0x03) == 2) {
        return ((uint64_t)PCI_read_dword(bus, slot, function, 0x10 + ((bar + 1) * 4)) << 32) | (bar_val & ~0x0f);
    }
    return 0;
}

/* Get the vendor and device ID of the PCI chipset */
PCIChipset PCI_get_chipset(void)
{
    PCIChipset chipset;
    chipset.Vendor = PCI_read_word(0, 0, 0, PCI_CFG_VENDOR);
    chipset.Device = PCI_read_word(0, 0, 0, PCI_CFG_DEVICE);
    return chipset;
}

/* Find PCI devices of the specified class, subclass, and programming interface */
uint8_t PCI_finl_device(uint8_t cls, uint8_t subcls, uint8_t programif)
{
    for (int bus = 0; bus < 256; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            for (int function = 0; function < 8; function++) {
                if (PCI_read_byte(bus, slot, function, PCI_CFG_CLASS) == cls && PCI_read_byte(bus, slot, function, PCI_CFG_SUBCLASS) == subcls
                    && PCI_read_byte(bus, slot, function, PCI_CFG_INTERFACE) == programif)
                    return 1;
            }
        }
    }
    return 0;
}

/* Find PCI devices of the specified class and subclass, regardless of programming interface */
uint8_t PCI_finl_deviceW(uint8_t cls, uint8_t subcls)
{
    for (int bus = 0; bus < 256; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            for (int function = 0; function < 8; function++) {
                if (PCI_read_byte(bus, slot, function, PCI_CFG_CLASS) == cls && PCI_read_byte(bus, slot, function, PCI_CFG_SUBCLASS) == subcls)
                    return 1;
            }
        }
    }
    return 0;
}
