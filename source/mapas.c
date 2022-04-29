
#include "mapas.h"
#include "estruturas.h"
//#include <bits/posix2_lim.h>

void leMapa(char *mapa, listaParede *lista, listaTerra *listTerra,
            listaCristal *listCristal, listaPedra *listPedra,
            listaMuro *listMuro, listaQuadrado *listQuadrado,  listaBorboleta *listBorboleta) {

  int flagParede = 0, flagTerra = 0, flagCristal = 0, flagPedra = 0,
      flagMuro = 0, flagQuadrado = 0, flagBorboleta =0;

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
  iniciaListaTerra(listTerra);
  iniciaListaCristal(listCristal);
  iniciaListaPedra(listPedra);
  iniciaListaQuadrado(listQuadrado);
  iniciaListaMuro(listMuro);
  iniciaListaParede(lista);
  iniciaListaBorboleta(listBorboleta);
  
  for (int i = 0; i < 22; i++) {
    for (int j = 0; j <= 40; j++) {
      fscanf(arq, "%c", &tile);
      switch (tile) {
      case 'W':
        if (flagParede == 0) {

          insListaVazParede(lista, j * 16, (i + 1) * 16);
          flagParede++;
        } else {
          insListaFimParede(lista, j * 16, (i + 1) * 16);
        }
        break;
      case '.':
        if (flagTerra == 0) {
          insListaVazTerra(listTerra, j * 16, (i + 1) * 16);
          flagTerra++;
        } else {
          insListaFimTerra(listTerra, j * 16, (i + 1) * 16);
        }
        break;
      case 'd':
        if (flagCristal == 0) {
          insListaVazCristal(listCristal, j * 16, (i + 1) * 16);
          flagCristal++;
        } else {
          insListaFimCristal(listCristal, j * 16, (i + 1) * 16);
        }
        break;
      case 'w':
        if (flagMuro == 0) {
          insListaVazMuro(listMuro, j * 16, (i + 1) * 16);
          flagMuro++;
        } else {
          insListaFimMuro(listMuro, j * 16, (i + 1) * 16);
        }
        break;
      case 'r':
        if (flagPedra == 0) {
          insListaVazPedra(listPedra, j * 16, (i + 1) * 16);
          flagPedra++;
        } else {
          insListaFimPedra(listPedra, j * 16, (i + 1) * 16);
        }
        break;
      case 'q':
        if (flagQuadrado == 0) {
          insListaVazQuadrado(listQuadrado, j * 16, (i + 1) * 16);
          flagQuadrado++;
        } else {
          insListaFimQuadrado(listQuadrado, j * 16, (i + 1) * 16);
        }
        break;
      case 'B':
        if (flagBorboleta == 0) {
          insListaVazBorboleta(listBorboleta, j * 16, (i + 1) * 16);
          flagBorboleta++;
        } else {
          insListaFimBorboleta(listBorboleta, j * 16, (i + 1) * 16);
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
