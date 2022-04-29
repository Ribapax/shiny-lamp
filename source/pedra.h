#ifndef __PEDRA__
#define __PEDRA__

#include "helper.h"
#include "estruturas.h"
#include "terra.h"



void iniciaListaPedra(listaPedra *lista);

int insListaVazPedra(listaPedra *lista, int x, int y);

int insListaFimPedra(listaPedra *lista, int x, int y);

int removListaPedra(listaPedra *lista, int x, int y);

void destruirListaPedra(listaPedra *lista);


void pedra_draw(SPRITESBD spritesbd, listaPedra lista);



void pedra_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                  listaCristal *listCristal, listaPedra *listPedra,
                  listaMuro *listMuro, listaQuadrado *listQuadrado,
                  listaBorboleta *listBorboleta, listaAmoeba *listAmoeba);



bool caiProLadoPedra(int x, int y, PLAYER *player, listaParede *lista,
                     listaTerra *listTerra, listaCristal *listCristal,
                     listaPedra *listPedra, listaMuro *listMuro,
                     listaQuadrado *listQuadrado, listaBorboleta *listBorboleta,
                     listaAmoeba *listAmoeba);

#endif
