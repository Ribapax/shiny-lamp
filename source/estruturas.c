
#include "estruturas.h"
#include <allegro5/allegro_audio.h>
#include <stdbool.h>
#include <stdio.h>

bool posicaoLivre(int x, int y, listaParede *lista, listaTerra *listTerra,
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

void porta_draw(SPRITESBD spritesbd, porta portal, PLAYER player) {

  if (player.cristais<player.cristnec)
    al_draw_bitmap(spritesbd.porta[0], portal.x, portal.y, 0);
  else
    al_draw_bitmap(spritesbd.porta[1], portal.x, portal.y, 0);
  
}
