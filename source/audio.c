
#include "audio.h"

ALLEGRO_SAMPLE * audio_init() {
  ALLEGRO_SAMPLE *moeda;
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(128);

  moeda = al_load_sample("resources/moeda.wav");
  must_init(moeda, "shot sample");
  return moeda;
}

void audio_deinit(ALLEGRO_SAMPLE *moeda) {
  al_destroy_sample(moeda);
}
