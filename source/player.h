#ifndef __PLAYER__
#define __PLAYER__

#include "helper.h"
#include "estruturas.h"



void player_init(PLAYER *player, int x, int y, int lives);

void player_update(PLAYER *player, unsigned char *key, listaParede *lista,
                   listaTerra *listTerra, listaCristal *listCristal,
                   listaPedra *listPedra, listaMuro *listMuro,
                   listaQuadrado *listQuadrado, listaBorboleta *listBorboleta,
                   listaAmoeba *listAmoeba, ALLEGRO_SAMPLE *moeda, int * score, int *nivel, bool *carregaMapa, porta porta);

void player_draw(PLAYER player, unsigned char *key, SPRITESBD spritesbd);

#endif
