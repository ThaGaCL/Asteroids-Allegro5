#ifndef ALLEGRO_AUDIO_H
#define ALLEGRO_AUDIO_H
#include "allegroUtil.h"

extern ALLEGRO_SAMPLE* sample_shot;
extern ALLEGRO_SAMPLE* sample_explode[2];

void audio_init();

void audio_deinit();

#endif