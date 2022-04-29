#ifndef __MAPAS__
#define __MAPAS__


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "quadrado.h"
#include "borboleta.h"
#include "terra.h"
#include "pedra.h"
#include "cristal.h"
#include "muro.h"
#include "amoeba.h"
#include "parede.h"

#define LINESIZE 40

void leMapa(char *mapa,PLAYER *player, listaParede *lista, listaTerra *listTerra,
            listaCristal *listCristal, listaPedra *listPedra,
            listaMuro *listMuro, listaQuadrado *listQuadrado,
            listaBorboleta *listBorboleta, listaAmoeba *listAmoeba);

#endif
