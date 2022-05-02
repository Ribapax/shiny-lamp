#include "pedra.h"


void pedra_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                  listaCristal *listCristal, listaPedra *listPedra,
                  listaMuro *listMuro, listaQuadrado *listQuadrado,
                  listaBorboleta *listBorboleta, listaAmoeba *listAmoeba, bool *teste) {

  if (player->frame % 8 == 0) {

    int prox_y, ant_y;
    pedra *em_andamento;

    em_andamento = listPedra->inicio;

    for (int i = 1; i <= listPedra->tamanho; ++i) {
      ant_y = em_andamento->y;
      prox_y = em_andamento->y + 16;

      if (em_andamento->x < 16)
        em_andamento->x = 16;

      if (em_andamento->x > PLAYER_MAX_X)
        em_andamento->x = PLAYER_MAX_X;
      if (prox_y > PLAYER_MAX_Y)
        prox_y = PLAYER_MAX_Y;
        
      if(player->x == em_andamento->x && player->y == prox_y && em_andamento->velocidade != 0)
        *teste = true;

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
      if(ant_y == em_andamento->y){
        em_andamento->velocidade = 0;
      }
      else {
        em_andamento->velocidade = 1;
      }

      em_andamento = em_andamento->proximo;
    }
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
  novaPedra->velocidade = 1;

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
  novaPedra->velocidade = 1;

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
