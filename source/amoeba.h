#ifndef __AMOEBA__
#define __AMOEBA__

#include "helper.h"
#include "estruturas.h"



void iniciaListaAmoeba(listaAmoeba *lista);

int insListaVazAmoeba(listaAmoeba *lista, int x, int y);

int insListaFimAmoeba(listaAmoeba *lista, int x, int y);

int removListaAmoeba(listaAmoeba *lista, int x, int y);

void destruirListaAmoeba(listaAmoeba *lista);

void amoeba_draw(SPRITESBD spritesbd, listaAmoeba lista);




#endif
