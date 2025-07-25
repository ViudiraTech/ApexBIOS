/*
 *      speaker.h
 *      Onboard buzzer driver header file
 *
 *      Based on GPL-3.0 open source agreement
 *      Copyright © 2020 ViudiraTech, based on the GPLv3 agreement.
 */

#ifndef INCLUDE_SPEAKER_H_
#define INCLUDE_SPEAKER_H_

#include "ports.h"

/* Activate the PC speakers to produce sound */
uint8_t pc_speaker_play(void);

/* Stop sound from PC speakers */
void pc_speaker_stop(void);

/* A short beep sounds */
void pc_speaker_beep(void);

#endif // INCLUDE_SPEAKER_H_
