#include "terra.h"



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
