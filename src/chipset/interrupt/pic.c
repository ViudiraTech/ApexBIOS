/*
 *      pic.c
 *      Programmable Interrupt Controller
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "pic.h"
#include "ports.h"

/* Initialize the master and slave PIC controllers */
void pic_init(uint8_t master_base, uint8_t slave_base)
{
    outb(PIC_MASTER_CMD, PIC_ICW1_INIT);
    outb(PIC_SLAVE_CMD, PIC_ICW1_INIT);

    outb(PIC_MASTER_DATA, master_base);
    outb(PIC_SLAVE_DATA, slave_base);

    outb(PIC_MASTER_DATA, 4);
    outb(PIC_SLAVE_DATA, 2);

    outb(PIC_MASTER_DATA, PIC_ICW4_8086);
    outb(PIC_SLAVE_DATA, PIC_ICW4_8086);

    outb(PIC_MASTER_DATA, 0xff);
    outb(PIC_SLAVE_DATA, 0xff);
}

/* Enable the specified IRQ */
void pic_enable_irq(uint8_t irq)
{
    if (irq > 15) return;
    if (irq > 7) {
        irq -= 8;
        outb(PIC_SLAVE_DATA, inb(PIC_SLAVE_DATA) & ~(1 << irq));
    } else {
        outb(PIC_MASTER_DATA, inb(PIC_MASTER_DATA) & ~(1 << irq));
    }
}

/* Disable the specified IRQ */
void pic_disable_irq(uint8_t irq)
{
    if (irq > 15) return;
    if (irq > 7) {
        irq -= 8;
        outb(PIC_SLAVE_DATA, inb(PIC_SLAVE_DATA) | (1 << irq));
    } else {
        outb(PIC_MASTER_DATA, inb(PIC_MASTER_DATA) | (1 << irq));
    }
}

/* Set the specified IRQ to level trigger mode */
void pic_set_level(uint8_t irq)
{
    if (irq > 15) return;
    if (irq > 7) {
        irq -= 8;
        outb(PIC_SLAVE_ELCR, inb(PIC_SLAVE_ELCR) | (1 << irq));
    } else {
        outb(PIC_MASTER_ELCR, inb(PIC_MASTER_ELCR) | (1 << irq));
    }
}

/* The specified IRQ is edge triggered */
void pic_set_edge(uint8_t irq)
{
    if (irq > 15) return;
    if (irq > 7) {
        irq -= 8;
        outb(PIC_SLAVE_ELCR, inb(PIC_SLAVE_ELCR) & ~(1 << irq));
    } else {
        outb(PIC_MASTER_ELCR, inb(PIC_MASTER_ELCR) & ~(1 << irq));
    }
}
