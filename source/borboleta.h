#ifndef __BORBOLETA__
#define __BORBOLETA__

#include "helper.h"
#include "estruturas.h"


void borboleta_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                     listaCristal *listCristal, listaPedra *listPedra,
                     listaMuro *listMuro, listaQuadrado *listQuadrado,
                     listaBorboleta *listBorboleta, listaAmoeba *listAmoeba);

void borboleta_draw(SPRITESBD spritesbd, listaBorboleta lista);


void iniciaListaBorboleta(listaBorboleta *lista);

int insListaVazBorboleta(listaBorboleta *lista, int x, int y);

int insListaFimBorboleta(listaBorboleta *lista, int x, int y);

int removListaBorboleta(listaBorboleta *lista, int x, int y);

void destruirListaBorboleta(listaBorboleta *lista);



#endif
