/*
 *      pic.h
 *      Programmable Interrupt Controller Header File
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_PIC_H_
#define INCLUDE_PIC_H_

#include "stdint.h"

#define PIC_MASTER_CMD  0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD   0xa0
#define PIC_SLAVE_DATA  0xa1
#define PIC_MASTER_ELCR 0x4d0
#define PIC_SLAVE_ELCR  0x4d1

#define PIC_ICW1_INIT ((1 << 4) | (1 << 0))
#define PIC_ICW4_8086 (1 << 0)

/* Initialize the master and slave PIC controllers */
void pic_init(uint8_t master_base, uint8_t slave_base);

/* Enable the specified IRQ */
void pic_enable_irq(uint8_t irq);

/* Disable the specified IRQ */
void pic_disable_irq(uint8_t irq);

/* Set the specified IRQ to level trigger mode */
void pic_set_level(uint8_t irq);

/* Set the specified IRQ to edge trigger mode */
void pic_set_edge(uint8_t irq);

#endif // INCLUDE_PIC_H_
