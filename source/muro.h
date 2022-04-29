#ifndef __MURO__
#define __MURO__

#include "helper.h"
#include "estruturas.h"


void iniciaListaMuro(listaMuro *lista);

int insListaVazMuro(listaMuro *lista, int x, int y);

int insListaFimMuro(listaMuro *lista, int x, int y);

int removListaMuro(listaMuro *lista, int x, int y);

void destruirListaMuro(listaMuro *lista);


void muro_draw(SPRITESBD spritesbd, listaMuro lista);



#endif
