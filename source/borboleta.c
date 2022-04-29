#include "borboleta.h"

void borboleta_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                     listaCristal *listCristal, listaPedra *listPedra,
                     listaMuro *listMuro, listaQuadrado *listQuadrado,
                     listaBorboleta *listBorboleta, listaAmoeba *listAmoeba) {

  if (player->frame % 8 == 0) {

    int prox_y, prox_x;
    borboleta *em_andamento;

    em_andamento = listBorboleta->inicio;

    for (int i = 1; i <= listBorboleta->tamanho; ++i) {
      prox_y = em_andamento->y;
      prox_x = em_andamento->x;
      if (em_andamento->dir == 1) { // direita
        if (posicaoLivre(em_andamento->x + 16, em_andamento->y, lista,
                         listTerra, listCristal, listPedra, listMuro,
                         listQuadrado, listBorboleta, listAmoeba))
          prox_x += 16;
        else
          em_andamento->dir = -2;
      } else if (em_andamento->dir == 2) { // baixo
        if (posicaoLivre(em_andamento->x, em_andamento->y + 16, lista,
                         listTerra, listCristal, listPedra, listMuro,
                         listQuadrado, listBorboleta, listAmoeba))
          prox_y += 16;
        else
          em_andamento->dir = 1;
      } else if (em_andamento->dir == -1) { // esquerda
        if (posicaoLivre(em_andamento->x - 16, em_andamento->y, lista,
                         listTerra, listCristal, listPedra, listMuro,
                         listQuadrado, listBorboleta, listAmoeba))
          prox_x -= 16;
        else
          em_andamento->dir = 2;
      } else if (em_andamento->dir == -2) { // cima
        if (posicaoLivre(em_andamento->x, em_andamento->y - 16, lista,
                         listTerra, listCristal, listPedra, listMuro,
                         listQuadrado, listBorboleta, listAmoeba))

          prox_y -= 16;
        else {
          em_andamento->dir = -1;
        }
      }

      if (em_andamento->x < 16)
        em_andamento->x = 16;

      if (em_andamento->x < 16)
        em_andamento->x = 16;

      if (em_andamento->x > PLAYER_MAX_X)
        em_andamento->x = PLAYER_MAX_X;
      if (prox_y > PLAYER_MAX_Y)
        prox_y = PLAYER_MAX_Y;

      if (findListaMuro(listMuro, prox_x, prox_y)) {
        prox_y = em_andamento->y;
        prox_x = em_andamento->x;
      } else if (findListaTerra(listTerra, prox_x, prox_y)) {

        prox_y = em_andamento->y;
        prox_x = em_andamento->x;
      }

      else if (findListaCristal(listCristal, prox_x, prox_y)) {
        prox_y = em_andamento->y;
        prox_x = em_andamento->x;

      } else if (findListaPedra(listPedra, prox_x, prox_y)) {
        prox_y = em_andamento->y;
        prox_x = em_andamento->x;
      } else if (em_andamento->x == player->x && prox_y == player->y)
        prox_y = em_andamento->y;

      em_andamento->y = prox_y;
      em_andamento->x = prox_x;
      em_andamento = em_andamento->proximo;
    }
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
  novaBorboleta->dir = -1;

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
  novaBorboleta->dir = -1;

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
