/*
 *      speaker.c
 *      Onboard buzzer driver
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#include "speaker.h"

/* Activate the PC speakers to produce sound */
uint8_t pc_speaker_play(void)
{
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t)(1193));
    outb(0x42, (uint8_t)(1193 >> 8));
    outb(0x61, inb(0x61) | 3);
}

/* Stop sound from PC speakers */
void pc_speaker_stop(void)
{
    outb(0x61, inb(0x61) & 0xFC);
}

/* A short beep sounds */
void pc_speaker_beep(void)
{
    pc_speaker_play();
    for (volatile int i = 0; i < 0xFFFFFF; i++) __asm__ volatile("nop");
    pc_speaker_stop();
    for (volatile int i = 0; i < 0xFFFFFF; i++) __asm__ volatile("nop");
}
