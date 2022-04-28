
#include "mapas.h"
#include "estruturas.h"
//#include <bits/posix2_lim.h>

void leMapa(char *mapa, listaParede *lista, listaTerra *listTerra, listaCristal *listCristal,listaPedra *listPedra, listaMuro *listMuro) {

  int flagParede = 0, flagTerra = 0, flagCristal = 0,flagPedra = 0, flagMuro = 0;

  FILE *arq;

  arq = fopen(mapa, "r");

  if (!arq) {
    perror("Erro ao abrir arquivo");
    exit(1);
  }

  // fprintf(arq, "%s", "teste\n");

  char tile;
  // unsigned char byte_value;
  //  img->matriz = alocarMatriz(img->width, img->height);
  ;

  for (int i = 0; i < 22; i++) {
    for (int j = 0; j <= 40; j++) {
      fscanf(arq, "%c", &tile);
      switch (tile) {
      case 'W':
        if (flagParede == 0) {
          iniciaListaParede(lista);
          insListaVazParede(lista, j * 16, (i + 1) * 16);
          flagParede++;
        } else {
          insListaFimParede(lista, j * 16, (i + 1) * 16);
        }
        break;
      case '.':
        if (flagTerra == 0) {
          iniciaListaTerra(listTerra);
          insListaVazTerra(listTerra, j * 16, (i + 1) * 16);
          flagTerra++;
        } else {
          insListaFimTerra(listTerra, j * 16, (i + 1) * 16);
        }
        break;
      case 'd':
        if (flagCristal == 0) {
          iniciaListaCristal(listCristal);
          insListaVazCristal(listCristal, j * 16, (i + 1) * 16);
          flagCristal++;
        } else {
          insListaFimCristal(listCristal, j * 16, (i + 1) * 16);
        }
        break;
      case 'w':
        if (flagMuro == 0) {
          iniciaListaMuro(listMuro);
          insListaVazMuro(listMuro, j * 16, (i + 1) * 16);
          flagMuro++;
        } else {
          insListaFimMuro(listMuro, j * 16, (i + 1) * 16);
        }
        break;
      case 'r':
        if (flagPedra == 0) {
          iniciaListaPedra(listPedra);
          insListaVazPedra(listPedra, j * 16, (i + 1) * 16);
          flagPedra++;
        } else {
          insListaFimPedra(listPedra, j * 16, (i + 1) * 16);
        }
        break;

      // case constante2:
      //   Instruções;
      //   break;

      //   default Instruções;
      }
    }
  }

  fclose(arq);
}
