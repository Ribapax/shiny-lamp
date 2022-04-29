#include "muro.h"


void muro_draw(SPRITESBD spritesbd, listaMuro lista) {
  muro *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.muro, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }
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
