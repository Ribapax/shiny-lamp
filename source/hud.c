
#include "hud.h"

void hud_draw(ALLEGRO_FONT *font, PLAYER *player, SPRITESBD *sprites, int score) {
  al_draw_textf(font, al_map_rgb(255, 247, 0), 20, 4, 0, "%d", player->cristnec);
  al_draw_bitmap(sprites->cristal[0], 38, 0, 0);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 56, 4, 0, "%d", player->pont);
  al_draw_bitmap(sprites->jogador[0], 300, 0, 0);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 318, 4, 0, "x %d", player->lives);
  al_draw_textf(font, al_map_rgb(255, 247, 0), 500, 4, 0, "%02d", player->cristais);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 550, 4, ALLEGRO_ALIGN_CENTRE,
                "%d", 120);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 570, 4, 0, "%06d",score);
}
