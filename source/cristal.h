#ifndef __CRISTAL__
#define __CRISTAL__

#include "helper.h"
#include "estruturas.h"



void iniciaListaCristal(listaCristal *lista);

int insListaVazCristal(listaCristal *lista, int x, int y);

int insListaFimCristal(listaCristal *lista, int x, int y);

void destruirListaCristal(listaCristal *lista);


void cristal_draw(SPRITESBD spritesbd, listaCristal lista);


void cristal_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                    listaCristal *listCristal, listaPedra *listPedra,
                    listaMuro *listMuro, listaQuadrado *listQuadrado,
                    listaBorboleta *listBorboleta, listaAmoeba *listAmoeba, bool *teste);



#endif
