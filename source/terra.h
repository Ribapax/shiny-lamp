#ifndef __TERRA__
#define __TERRA__

#include "helper.h"
#include "estruturas.h"




void iniciaListaTerra(listaTerra *lista);

int insListaVazTerra(listaTerra *lista, int x, int y);

int insListaFimTerra(listaTerra *lista, int x, int y);

void destruirListaTerra(listaTerra *lista);

void dirt_draw(SPRITESBD spritesbd, listaTerra lista);


#endif
