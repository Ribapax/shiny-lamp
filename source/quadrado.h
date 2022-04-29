#ifndef __QUADRADO__
#define __QUADRADO__

#include "helper.h"
#include "estruturas.h"



void iniciaListaQuadrado(listaQuadrado *lista);

int insListaVazQuadrado(listaQuadrado *lista, int x, int y);

int insListaFimQuadrado(listaQuadrado *lista, int x, int y);

int removListaQuadrado(listaQuadrado *lista, int x, int y);

void destruirListaQuadrado(listaQuadrado *lista);


void quadrado_draw(SPRITESBD spritesbd, listaQuadrado lista);


void quadrado_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                     listaCristal *listCristal, listaPedra *listPedra,
                     listaMuro *listMuro, listaQuadrado *listQuadrado,
                     listaBorboleta *listBorboleta, listaAmoeba *listAmoeba);


#endif
