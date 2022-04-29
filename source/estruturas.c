
#include "estruturas.h"
#include <allegro5/allegro_audio.h>
#include <stdbool.h>
#include <stdio.h>

void player_init(PLAYER *player, int x, int y) {
  player->x = x;
  player->y = y;
  player->frame = 0;
}

void pedra_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                  listaCristal *listCristal, listaPedra *listPedra,
                  listaMuro *listMuro, listaQuadrado *listQuadrado,
                  listaBorboleta *listBorboleta, listaAmoeba *listAmoeba) {

  if (player->frame % 8 == 0) {

    int prox_y;
    pedra *em_andamento;

    em_andamento = listPedra->inicio;

    for (int i = 1; i <= listPedra->tamanho; ++i) {
      prox_y = em_andamento->y + 16;

      if (em_andamento->x < 16)
        em_andamento->x = 16;

      if (em_andamento->x > PLAYER_MAX_X)
        em_andamento->x = PLAYER_MAX_X;
      if (prox_y > PLAYER_MAX_Y)
        prox_y = PLAYER_MAX_Y;

      if (findListaMuro(listMuro, em_andamento->x, prox_y)) {
        prox_y = em_andamento->y;
        if (posicaoLivrePedra(em_andamento->x - 16, prox_y, lista, listTerra,
                              listCristal, listPedra, listMuro, listQuadrado,
                              listBorboleta, listAmoeba) &&
            posicaoLivrePedra(em_andamento->x - 16, prox_y + 16, lista,
                              listTerra, listCristal, listPedra, listMuro,
                              listQuadrado, listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x - 16 || player->y != prox_y) &&
             (player->x != em_andamento->x - 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x - 16;
        }
        if (posicaoLivrePedra(em_andamento->x + 16, prox_y, lista, listTerra,
                              listCristal, listPedra, listMuro, listQuadrado,
                              listBorboleta, listAmoeba) &&
            posicaoLivrePedra(em_andamento->x + 16, prox_y + 16, lista,
                              listTerra, listCristal, listPedra, listMuro,
                              listQuadrado, listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x + 16 || player->y != prox_y) &&
             (player->x != em_andamento->x + 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x + 16;
        }
      } else if (findListaTerra(listTerra, em_andamento->x, prox_y))
        prox_y = em_andamento->y;

      else if (findListaCristal(listCristal, em_andamento->x, prox_y)) {
        prox_y = em_andamento->y;
        if (posicaoLivrePedra(em_andamento->x - 16, prox_y, lista, listTerra,
                              listCristal, listPedra, listMuro, listQuadrado,
                              listBorboleta, listAmoeba) &&
            posicaoLivrePedra(em_andamento->x - 16, prox_y + 16, lista,
                              listTerra, listCristal, listPedra, listMuro,
                              listQuadrado, listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x - 16 || player->y != prox_y) &&
             (player->x != em_andamento->x - 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x - 16;
        }
        if (posicaoLivrePedra(em_andamento->x + 16, prox_y, lista, listTerra,
                              listCristal, listPedra, listMuro, listQuadrado,
                              listBorboleta, listAmoeba) &&
            posicaoLivrePedra(em_andamento->x + 16, prox_y + 16, lista,
                              listTerra, listCristal, listPedra, listMuro,
                              listQuadrado, listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x + 16 || player->y != prox_y) &&
             (player->x != em_andamento->x + 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x + 16;
        }

      } else if (findListaPedra(listPedra, em_andamento->x, prox_y)) {
        prox_y = em_andamento->y;
        if (posicaoLivrePedra(em_andamento->x - 16, prox_y, lista, listTerra,
                              listCristal, listPedra, listMuro, listQuadrado,
                              listBorboleta, listAmoeba) &&
            posicaoLivrePedra(em_andamento->x - 16, prox_y + 16, lista,
                              listTerra, listCristal, listPedra, listMuro,
                              listQuadrado, listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x - 16 || player->y != prox_y) &&
             (player->x != em_andamento->x - 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x - 16;
        }
        if (posicaoLivrePedra(em_andamento->x + 16, prox_y, lista, listTerra,
                              listCristal, listPedra, listMuro, listQuadrado,
                              listBorboleta, listAmoeba) &&
            posicaoLivrePedra(em_andamento->x + 16, prox_y + 16, lista,
                              listTerra, listCristal, listPedra, listMuro,
                              listQuadrado, listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x + 16 || player->y != prox_y) &&
             (player->x != em_andamento->x + 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x + 16;
        }
      } else if (em_andamento->x == player->x && prox_y == player->y)
        prox_y = em_andamento->y;

      em_andamento->y = prox_y;
      em_andamento = em_andamento->proximo;
    }
  }
}

void player_update(PLAYER *player, unsigned char *key, listaParede *lista,
                   listaTerra *listTerra, listaCristal *listCristal,
                   listaPedra *listPedra, listaMuro *listMuro,
                   listaQuadrado *listQuadrado, listaBorboleta *listBorboleta,
                   listaAmoeba *listAmoeba, ALLEGRO_SAMPLE *moeda) {

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
    if (findListaPedra(listPedra, prox_x, prox_y)) {
      if (posicaoLivrePedra(prox_x + (dir * 16), prox_y, lista, listTerra,
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
      al_play_sample(moeda, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    };

    player->x = prox_x;
    player->y = prox_y;
  }
  player->frame++;
}

bool posicaoLivrePedra(int x, int y, listaParede *lista, listaTerra *listTerra,
                       listaCristal *listCristal, listaPedra *listPedra,
                       listaMuro *listMuro, listaQuadrado *listQuadrado,
                       listaBorboleta *listBorboleta, listaAmoeba *listAmoeba) {
  if (findListaMuro(listMuro, x, y))
    return false;
  if (findListaTerra(listTerra, x, y))
    return false;
  if (findListaCristal(listCristal, x, y))
    return false;
  if (findListaPedra(listPedra, x, y))
    return false;
  if (findListaParede(lista, x, y))
    return false;
  // if (player->x == x && player->y == y ){
  //   return false;
  // }

  return true;
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

void dirt_draw(SPRITESBD spritesbd, listaTerra lista) {
  // int espaco = TILE;
  terra *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.dirt, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }

  // for (int i = 0; i < DIRTS_N; i++) {
  //   if (dirts[i].used == false)
  //     al_draw_bitmap(spritesbd.dirt, dirts[i].x, dirts[i].y, 0);
  // }
}

void muro_draw(SPRITESBD spritesbd, listaMuro lista) {
  muro *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.muro, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }
}

void pedra_draw(SPRITESBD spritesbd, listaPedra lista) {
  pedra *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.pedra, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }
}

void cristal_draw(SPRITESBD spritesbd, listaCristal lista) {
  // int espaco = TILE;
  int frame_display;

  cristal *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    frame_display = (em_andamento->frame / 5) % 8;

    al_draw_bitmap(spritesbd.cristal[frame_display], em_andamento->x,
                   em_andamento->y, 0);
    em_andamento->frame++;
    em_andamento = em_andamento->proximo;
  }

  // for (int i = 0; i < CRISTAL_N; i++) {
  //   if (cristals[i].used == false) {
  //     frame_display = (cristals[i].frame / 5) % 8;
  //     al_draw_bitmap(spritesbd.cristal[frame_display], cristals[i].x,
  //                    cristals[i].y, 0);
  //     cristals[i].frame++;
  //   }
  // al_draw_bitmap(spritesbd.dirt,dirts[i].x,dirts[i].y, 0);
  // }
}

void quadrado_draw(SPRITESBD spritesbd, listaQuadrado lista) {
  // int espaco = TILE;
  int frame_display;

  quadrado *em_andamento;

  em_andamento = lista.inicio;

  for (int i = 1; i <= lista.tamanho; i++) {
    frame_display = (em_andamento->frame / 5) % 4;

    al_draw_bitmap(spritesbd.quadrado[frame_display], em_andamento->x,
                   em_andamento->y, 0);
    em_andamento->frame++;
    em_andamento = em_andamento->proximo;
  }
}

void borboleta_draw(SPRITESBD spritesbd, listaBorboleta lista) {
  // int espaco = TILE;
  int frame_display;

  borboleta *em_andamento;

  em_andamento = lista.inicio;

  for (int i = 1; i <= lista.tamanho; i++) {
    frame_display = (em_andamento->frame / 5) % 4;

    al_draw_bitmap(spritesbd.borboleta[frame_display], em_andamento->x,
                   em_andamento->y, 0);
    em_andamento->frame++;
    em_andamento = em_andamento->proximo;
  }
}

void amoeba_draw(SPRITESBD spritesbd, listaAmoeba lista) {
  // int espaco = TILE;
  int frame_display;

  amoeba *em_andamento;

  em_andamento = lista.inicio;

  for (int i = 1; i <= lista.tamanho; i++) {
    frame_display = (em_andamento->frame / 5) % 4;

    al_draw_bitmap(spritesbd.amoeba[frame_display], em_andamento->x,
                   em_andamento->y, 0);
    em_andamento->frame++;
    em_andamento = em_andamento->proximo;
  }
}

void wall_draw(SPRITESBD spritesbd, listaParede lista) {
  // int espaco = TILE; // espaço no inicio da tela onde fica HUD do jogador

  parede *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.wall, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }

  // for (int i = espaco; i < BUFFER_H; i += TILE) {
  //   for (int j = 0; j < BUFFER_W; j += TILE) {
  //     if (i == espaco || j == 0 || i == BUFFER_H - TILE || j == BUFFER_W -
  //     TILE)
  //       al_draw_bitmap(spritesbd.wall, j, i, 0);
  //     // else
  //     //     al_draw_bitmap(spritesbd.dirt, j, i, 0);
  //   }
  // }
}

void iniciaListaMuro(listaMuro *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazMuro(listaMuro *lista, int x, int y) {

  muro *novaMuro;
  if ((novaMuro = malloc(sizeof(muro))) == NULL)
    return -1;

  novaMuro->x = x;
  novaMuro->y = y;

  novaMuro->anterior = lista->inicio;
  novaMuro->proximo = lista->fim;

  lista->inicio = novaMuro;
  lista->fim = novaMuro;
  lista->tamanho++;
  return 0;
}

int insListaFimMuro(listaMuro *lista, int x, int y) {
  muro *novaMuro;
  if ((novaMuro = malloc(sizeof(muro))) == NULL)
    return -1;

  novaMuro->x = x;
  novaMuro->y = y;

  novaMuro->proximo = NULL;
  novaMuro->anterior = lista->fim;

  lista->fim->proximo = novaMuro;
  lista->fim = novaMuro;
  lista->tamanho++;

  return 0;
}

bool findListaMuro(listaMuro *lista, int x, int y) {
  muro *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      return true;
    em_andamento = em_andamento->proximo;
  }
  return false;
}

bool findListaTerra(listaTerra *lista, int x, int y) {
  terra *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      return true;
    em_andamento = em_andamento->proximo;
  }
  return false;
}

bool findListaPedra(listaPedra *lista, int x, int y) {
  pedra *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      return true;
    em_andamento = em_andamento->proximo;
  }
  return false;
}

bool findListaParede(listaParede *lista, int x, int y) {
  parede *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      return true;
    em_andamento = em_andamento->proximo;
  }
  return false;
}

void changeListaPedra(listaPedra *lista, int x, int y, int x_novo) {
  pedra *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y) {
      em_andamento->x = x_novo;
      // em_andamento->y = y_novo;
    }

    em_andamento = em_andamento->proximo;
  }
}

bool findListaCristal(listaCristal *lista, int x, int y) {
  cristal *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      return true;
    em_andamento = em_andamento->proximo;
  }
  return false;
}

int removListaMuro(listaMuro *lista, int x, int y) {
  int pos = -1;
  muro *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0 || pos == -1)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaMuro(listaMuro *lista) {
  muro *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaPedra(listaPedra *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazPedra(listaPedra *lista, int x, int y) {

  pedra *novaPedra;
  if ((novaPedra = malloc(sizeof(pedra))) == NULL)
    return -1;

  novaPedra->x = x;
  novaPedra->y = y;

  novaPedra->anterior = lista->inicio;
  novaPedra->proximo = lista->fim;

  lista->inicio = novaPedra;
  lista->fim = novaPedra;
  lista->tamanho++;
  return 0;
}

int insListaFimPedra(listaPedra *lista, int x, int y) {
  pedra *novaPedra;
  if ((novaPedra = malloc(sizeof(pedra))) == NULL)
    return -1;

  novaPedra->x = x;
  novaPedra->y = y;

  novaPedra->proximo = NULL;
  novaPedra->anterior = lista->fim;

  lista->fim->proximo = novaPedra;
  lista->fim = novaPedra;
  lista->tamanho++;

  return 0;
}

int removListaPedra(listaPedra *lista, int x, int y) {
  int pos;
  pedra *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaPedra(listaPedra *lista) {
  pedra *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaTerra(listaTerra *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazTerra(listaTerra *lista, int x, int y) {

  terra *novaTerra;
  if ((novaTerra = malloc(sizeof(terra))) == NULL)
    return -1;

  novaTerra->x = x;
  novaTerra->y = y;

  novaTerra->anterior = lista->inicio;
  novaTerra->proximo = lista->fim;

  lista->inicio = novaTerra;
  lista->fim = novaTerra;
  lista->tamanho++;
  return 0;
}

int insListaFimTerra(listaTerra *lista, int x, int y) {
  terra *novaTerra;
  if ((novaTerra = malloc(sizeof(terra))) == NULL)
    return -1;

  novaTerra->x = x;
  novaTerra->y = y;

  novaTerra->proximo = NULL;
  novaTerra->anterior = lista->fim;

  lista->fim->proximo = novaTerra;
  lista->fim = novaTerra;
  lista->tamanho++;

  return 0;
}

int removListaTerra(listaTerra *lista, int x, int y) {
  int pos = -1;
  terra *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0 || pos == -1)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaTerra(listaTerra *lista) {
  terra *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaParede(listaParede *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazParede(listaParede *lista, int x, int y) {

  parede *novaParede;
  if ((novaParede = malloc(sizeof(parede))) == NULL)
    return -1;

  novaParede->x = x;
  novaParede->y = y;

  novaParede->anterior = lista->inicio;
  novaParede->proximo = lista->fim;

  lista->inicio = novaParede;
  lista->fim = novaParede;
  lista->tamanho++;
  return 0;
}

int insListaFimParede(listaParede *lista, int x, int y) {
  parede *novaParede;
  if ((novaParede = malloc(sizeof(parede))) == NULL)
    return -1;

  novaParede->x = x;
  novaParede->y = y;

  novaParede->proximo = NULL;
  novaParede->anterior = lista->fim;

  lista->fim->proximo = novaParede;
  lista->fim = novaParede;
  lista->tamanho++;

  return 0;
}

int removListaParede(listaParede *lista, int x, int y) {
  int pos;
  parede *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaParede(listaParede *lista) {
  parede *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaQuadrado(listaQuadrado *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazQuadrado(listaQuadrado *lista, int x, int y) {

  quadrado *novaQuadrado;
  if ((novaQuadrado = malloc(sizeof(quadrado))) == NULL)
    return -1;

  novaQuadrado->x = x;
  novaQuadrado->y = y;
  novaQuadrado->frame = 0;

  novaQuadrado->anterior = lista->inicio;
  novaQuadrado->proximo = lista->fim;

  lista->inicio = novaQuadrado;
  lista->fim = novaQuadrado;
  lista->tamanho++;
  return 0;
}

int insListaFimQuadrado(listaQuadrado *lista, int x, int y) {
  quadrado *novaQuadrado;
  if ((novaQuadrado = malloc(sizeof(quadrado))) == NULL)
    return -1;

  novaQuadrado->x = x;
  novaQuadrado->y = y;
  novaQuadrado->frame = 0;

  novaQuadrado->proximo = NULL;
  novaQuadrado->anterior = lista->fim;

  lista->fim->proximo = novaQuadrado;
  lista->fim = novaQuadrado;
  lista->tamanho++;

  return 0;
}

int removListaQuadrado(listaQuadrado *lista, int x, int y) {
  int pos;
  quadrado *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaQuadrado(listaQuadrado *lista) {
  quadrado *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaBorboleta(listaBorboleta *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazBorboleta(listaBorboleta *lista, int x, int y) {

  borboleta *novaBorboleta;
  if ((novaBorboleta = malloc(sizeof(borboleta))) == NULL)
    return -1;

  novaBorboleta->x = x;
  novaBorboleta->y = y;
  novaBorboleta->frame = 0;

  novaBorboleta->anterior = lista->inicio;
  novaBorboleta->proximo = lista->fim;

  lista->inicio = novaBorboleta;
  lista->fim = novaBorboleta;
  lista->tamanho++;
  return 0;
}

int insListaFimBorboleta(listaBorboleta *lista, int x, int y) {
  borboleta *novaBorboleta;
  if ((novaBorboleta = malloc(sizeof(borboleta))) == NULL)
    return -1;

  novaBorboleta->x = x;
  novaBorboleta->y = y;
  novaBorboleta->frame = 0;

  novaBorboleta->proximo = NULL;
  novaBorboleta->anterior = lista->fim;

  lista->fim->proximo = novaBorboleta;
  lista->fim = novaBorboleta;
  lista->tamanho++;

  return 0;
}

int removListaBorboleta(listaBorboleta *lista, int x, int y) {
  int pos;
  borboleta *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaBorboleta(listaBorboleta *lista) {
  borboleta *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaAmoeba(listaAmoeba *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazAmoeba(listaAmoeba *lista, int x, int y) {

  amoeba *novaAmoeba;
  if ((novaAmoeba = malloc(sizeof(amoeba))) == NULL)
    return -1;

  novaAmoeba->x = x;
  novaAmoeba->y = y;
  novaAmoeba->frame = 0;

  novaAmoeba->anterior = lista->inicio;
  novaAmoeba->proximo = lista->fim;

  lista->inicio = novaAmoeba;
  lista->fim = novaAmoeba;
  lista->tamanho++;
  return 0;
}

int insListaFimAmoeba(listaAmoeba *lista, int x, int y) {
  amoeba *novaAmoeba;
  if ((novaAmoeba = malloc(sizeof(amoeba))) == NULL)
    return -1;

  novaAmoeba->x = x;
  novaAmoeba->y = y;
  novaAmoeba->frame = 0;

  novaAmoeba->proximo = NULL;
  novaAmoeba->anterior = lista->fim;

  lista->fim->proximo = novaAmoeba;
  lista->fim = novaAmoeba;
  lista->tamanho++;

  return 0;
}

int removListaAmoeba(listaAmoeba *lista, int x, int y) {
  int pos;
  amoeba *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaAmoeba(listaAmoeba *lista) {
  amoeba *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaCristal(listaCristal *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazCristal(listaCristal *lista, int x, int y) {

  cristal *novaCristal;
  if ((novaCristal = malloc(sizeof(cristal))) == NULL)
    return -1;

  novaCristal->x = x;
  novaCristal->y = y;
  novaCristal->frame = 0;

  novaCristal->anterior = lista->inicio;
  novaCristal->proximo = lista->fim;

  lista->inicio = novaCristal;
  lista->fim = novaCristal;
  lista->tamanho++;
  return 0;
}

int insListaFimCristal(listaCristal *lista, int x, int y) {
  cristal *novaCristal;
  if ((novaCristal = malloc(sizeof(cristal))) == NULL)
    return -1;

  novaCristal->x = x;
  novaCristal->y = y;
  novaCristal->frame = 0;

  novaCristal->proximo = NULL;
  novaCristal->anterior = lista->fim;

  lista->fim->proximo = novaCristal;
  lista->fim = novaCristal;
  lista->tamanho++;

  return 0;
}

int removListaCristal(listaCristal *lista, int x, int y) {
  int pos = -1;
  cristal *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i <= lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0 || pos == -1)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaCristal(listaCristal *lista) {
  cristal *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}
