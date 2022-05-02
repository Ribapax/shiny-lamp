#include "player.h"
#include "estruturas.h"

void player_init(PLAYER *player, int x, int y, int lives) {
  player->x = x;
  player->y = y;
  player->frame = 0;
  player->cristais = 0;
  player->lives = lives;
}

void player_update(PLAYER *player, unsigned char *key, listaParede *lista,
                   listaTerra *listTerra, listaCristal *listCristal,
                   listaPedra *listPedra, listaMuro *listMuro,
                   listaQuadrado *listQuadrado, listaBorboleta *listBorboleta,
                   listaAmoeba *listAmoeba, ALLEGRO_SAMPLE *moeda, int *score,
                   int *nivel, bool *carregaMapa, porta porta) {

  if (player->frame % 6 == 0) {
    int prox_x = player->x, prox_y = player->y;
    int dir = 0;

    if (key[ALLEGRO_KEY_LEFT]) {
      dir = -1;
      prox_x = player->x - 16;
    } else if (key[ALLEGRO_KEY_RIGHT]) {
      dir = +1;
      prox_x = player->x + 16;
    } else if (key[ALLEGRO_KEY_UP])
      prox_y = player->y - 16;
    else if (key[ALLEGRO_KEY_DOWN])
      prox_y = player->y + 16;

    if (prox_x < 16)
      prox_x = 16;
    if (prox_y < 32)
      prox_y = 32;

    if (prox_x > PLAYER_MAX_X)
      prox_x = PLAYER_MAX_X;
    if (prox_y > PLAYER_MAX_Y)
      prox_y = PLAYER_MAX_Y;

    if (findListaMuro(listMuro, prox_x, prox_y)) {
      prox_x = player->x;
      prox_y = player->y;
    }

    if (prox_x == porta.x && prox_y == porta.y) {
      if (player->cristais < player->cristnec) {
        prox_x = player->x;
        prox_y = player->y;
      } else {
        *nivel = *nivel + 1;
        *carregaMapa = true;
      }
    }

    if (findListaPedra(listPedra, prox_x, prox_y)) {
      if (posicaoLivre(prox_x + (dir * 16), prox_y, lista, listTerra,
                       listCristal, listPedra, listMuro, listQuadrado,
                       listBorboleta, listAmoeba)) {

        changeListaPedra(listPedra, prox_x, prox_y, prox_x + (dir * 16));
      } else {
        prox_x = player->x;
        prox_y = player->y;
      }
    }

    removListaTerra(listTerra, prox_x, prox_y);
    if (removListaCristal(listCristal, prox_x, prox_y) == 0) {
      if (player->cristais < player->cristnec)
        *score = *score + player->pont;
      else
        *score = *score + player->pont * 1.5;

      player->cristais++;
      al_play_sample(moeda, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    };

    player->x = prox_x;
    player->y = prox_y;
  }
  player->frame++;
}

void player_draw(PLAYER player, unsigned char *key, SPRITESBD spritesbd) {

  int frame_display = (player.frame / 10) % 7;

  // if(shots[i].ship)
  if (key[ALLEGRO_KEY_LEFT])
    al_draw_bitmap(spritesbd.jogadorEsq[frame_display], player.x, player.y, 0);
  else if (key[ALLEGRO_KEY_RIGHT])
    al_draw_bitmap(spritesbd.jogadorDir[frame_display], player.x, player.y, 0);
  else
    al_draw_bitmap(spritesbd.jogador[frame_display], player.x, player.y, 0);
  // al_draw_bitmap(sprites.ship_shot[frame_display], shots[i].x, shots[i].y,
  // 0);
  /* else // alien
  {
      ALLEGRO_COLOR tint =
          frame_display
          ? al_map_rgb_f(1, 1, 1)
          : al_map_rgb_f(0.5, 0.5, 0.5)
      ;
      al_draw_tinted_bitmap(sprites.alien_shot, tint, shots[i].x, shots[i].y,
  0);
  } */
}
