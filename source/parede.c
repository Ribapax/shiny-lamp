#include "parede.h"


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
