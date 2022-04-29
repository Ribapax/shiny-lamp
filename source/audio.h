#ifndef __HELP__
#define __HELP__

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "helper.h"

ALLEGRO_SAMPLE * audio_init();
void audio_deinit(ALLEGRO_SAMPLE *moeda);

#endif
