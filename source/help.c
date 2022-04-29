#include "help.h"


void help_draw(ALLEGRO_FONT *font) {
  al_draw_filled_rectangle(0, 0, BUFFER_W, BUFFER_H, al_map_rgba(0, 0, 0, 100));
  al_draw_filled_rectangle(TILE * 2, TILE * 3, BUFFER_W - TILE * 2,
                           BUFFER_H - TILE * 2,
                           al_map_rgba(100, 100, 100, 255));
  al_draw_text(font, al_map_rgb(0, 0, 0), BUFFER_W / 2, TILE * 4,
               ALLEGRO_ALIGN_CENTRE, "HELP");
  al_draw_multiline_text(
      font, al_map_rgb(0, 0, 0), BUFFER_W / 2, TILE * 6, BUFFER_W, 34,
      ALLEGRO_ALIGN_CENTRE,
      "Seguem as instruções para jogar o jogo");
  al_draw_multiline_text(
      font, al_map_rgb(0, 0, 0), TILE * 3, TILE * 8, BUFFER_W * 8 / 10, 16, 0,
      "Colete os cristais necessários para liberar a saida, não esqueça de olhar para cima "
      "a previsão do tempo é de pedrada.");
  al_draw_multiline_text(
      font, al_map_rgb(0, 0, 0), TILE * 3, TILE * 11, BUFFER_W * 8 / 10, 16, 0,
      "- Use as teclas direcionais para mover o seu personagem.");
  /* al_draw_multiline_text(font, al_map_rgb(0, 0, 0), 340, 360, 600, 16, 0,
                         "- Press R to restart your level, but be aware that "
                         "you will lose one life.");*/
  /* al_draw_multiline_text(font, al_map_rgb(0, 0, 0), TILE * 3, TILE * 13, 600,
                         16, 0,
                         "- Press K L N together to get 5 extra lives, but you "
                         "can use it only once."); */
  al_draw_text(font, al_map_rgb(0, 0, 0), (BUFFER_W / 2), TILE * 19,
               ALLEGRO_ALIGN_CENTRE,
               "Desenvolvido por Mateus Ribamar da Paixão");
  al_draw_text(font, al_map_rgb(0, 0, 0), (BUFFER_W / 2) + 40, TILE * 20, 0,
               "Press h or F1 to play");
}