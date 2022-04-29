#ifndef __MAPAS__
#define __MAPAS__

#include "estruturas.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 40

void leMapa(char *mapa,PLAYER *player, listaParede *lista, listaTerra *listTerra,
            listaCristal *listCristal, listaPedra *listPedra,
            listaMuro *listMuro, listaQuadrado *listQuadrado,
            listaBorboleta *listBorboleta, listaAmoeba *listAmoeba);

#endif
