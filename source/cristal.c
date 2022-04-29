#include "cristal.h"

void cristal_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                    listaCristal *listCristal, listaPedra *listPedra,
                    listaMuro *listMuro, listaQuadrado *listQuadrado,
                    listaBorboleta *listBorboleta, listaAmoeba *listAmoeba) {

  if (player->frame % 8 == 0) {

    int prox_y;
    cristal *em_andamento;

    em_andamento = listCristal->inicio;

    for (int i = 1; i <= listCristal->tamanho; ++i) {
      prox_y = em_andamento->y + 16;

      if (em_andamento->x < 16)
        em_andamento->x = 16;

      if (em_andamento->x > PLAYER_MAX_X)
        em_andamento->x = PLAYER_MAX_X;
      if (prox_y > PLAYER_MAX_Y)
        prox_y = PLAYER_MAX_Y;

      if (findListaMuro(listMuro, em_andamento->x, prox_y)) {
        prox_y = em_andamento->y;
        if (posicaoLivre(em_andamento->x - 16, prox_y, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            posicaoLivre(em_andamento->x - 16, prox_y + 16, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x - 16 || player->y != prox_y) &&
             (player->x != em_andamento->x - 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x - 16;
        }
        if (posicaoLivre(em_andamento->x + 16, prox_y, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            posicaoLivre(em_andamento->x + 16, prox_y + 16, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x + 16 || player->y != prox_y) &&
             (player->x != em_andamento->x + 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x + 16;
        }
      } else if (findListaTerra(listTerra, em_andamento->x, prox_y))
        prox_y = em_andamento->y;

      else if (findListaCristal(listCristal, em_andamento->x, prox_y)) {
        prox_y = em_andamento->y;
        if (posicaoLivre(em_andamento->x - 16, prox_y, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            posicaoLivre(em_andamento->x - 16, prox_y + 16, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x - 16 || player->y != prox_y) &&
             (player->x != em_andamento->x - 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x - 16;
        }
        if (posicaoLivre(em_andamento->x + 16, prox_y, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            posicaoLivre(em_andamento->x + 16, prox_y + 16, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x + 16 || player->y != prox_y) &&
             (player->x != em_andamento->x + 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x + 16;
        }

      } else if (findListaPedra(listPedra, em_andamento->x, prox_y)) {
        prox_y = em_andamento->y;
        if (posicaoLivre(em_andamento->x - 16, prox_y, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            posicaoLivre(em_andamento->x - 16, prox_y + 16, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            ((player->x != em_andamento->x - 16 || player->y != prox_y) &&
             (player->x != em_andamento->x - 16 || player->y != prox_y + 16))) {
          em_andamento->x = em_andamento->x - 16;
        }
        if (posicaoLivre(em_andamento->x + 16, prox_y, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
            posicaoLivre(em_andamento->x + 16, prox_y + 16, lista, listTerra,
                         listCristal, listPedra, listMuro, listQuadrado,
                         listBorboleta, listAmoeba) &&
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
