#include "amoeba.h"


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
