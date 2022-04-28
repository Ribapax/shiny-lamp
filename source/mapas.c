
#include "mapas.h"
#include "estruturas.h"
//#include <bits/posix2_lim.h>

void leMapa(char *mapa, listaParede *lista) {

  int flagParede = 0;

  FILE *arq;

  arq = fopen(mapa, "r");

  if (!arq) {
    perror("Erro ao abrir arquivo");
    exit(1);
  }

  // fprintf(arq, "%s", "teste\n");

  
  char tile;
  //unsigned char byte_value;
  // img->matriz = alocarMatriz(img->width, img->height);
  ;

  for (int i = 0; i < 22; i++) {
    for (int j = 0; j <= 40; j++) {
      fscanf(arq, "%c", &tile);
      if (tile=='w') {
        if(flagParede == 0){
          iniciaListaParede(lista);
          insListaVazParede(lista, j*16, (i+1)*16);
          flagParede++;
        }
        else {
          insListaFimParede(lista, j*16, (i+1)*16);
        }
      }
      
    }
  }

  fclose(arq);
}
