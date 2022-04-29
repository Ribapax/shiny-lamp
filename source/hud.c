
#include "hud.h"

void hud_draw(ALLEGRO_FONT *font, PLAYER *player, SPRITESBD *sprites, int score) {
  al_draw_textf(font, al_map_rgb(255, 247, 0), 16, 0, 0, "%d", 10);
  al_draw_bitmap(sprites->cristal[0], 105, 0, 0);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 155, 0, 0, "%d", 20);
  al_draw_bitmap(sprites->jogador[0], 300, 0, 0);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 340, 0, 0, "%d", 3);
  al_draw_textf(font, al_map_rgb(255, 247, 0), 500, 0, 0, "%02d", 7);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 550, 0, ALLEGRO_ALIGN_CENTRE,
                "%d", 120);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 570, 0, 0, "%06d",score);
}
