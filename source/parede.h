#ifndef __PAREDE__
#define __PAREDE__

#include "helper.h"
#include "estruturas.h"


void iniciaListaParede(listaParede *lista);

int insListaVazParede(listaParede *lista, int x, int y);

int insListaFimParede(listaParede *lista, int x, int y);

int removListaParede(listaParede *lista, int x, int y);

void destruirListaParede(listaParede *lista);


void wall_draw(SPRITESBD spritesbd, listaParede lista);


#endif
