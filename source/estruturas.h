#ifndef __ESTRUTURAS__
#define __ESTRUTURAS__

#include <allegro5/allegro5.h>
#include "helper.h"
#include "sprites.h"
#include <stdlib.h>


#define PLAYER_MAX_X (BUFFER_W - 2 * TILE)
#define PLAYER_MAX_Y (BUFFER_H - 2 * TILE)



// typedef enum tipo{
//   //terra = 0,
//   vazio,
//   pedra,
//   muro,
//   parede
// }tipo;

// typedef struct dl_elementoLista {   
//   char *dado;   
//   struct dl_elementoLista *anterior;   
//   struct dl_elementoLista *seguinte;   
// }dl_elemento;
//

typedef struct terra{
  int x, y;
  struct terra *proximo;
  struct terra *anterior;
}terra;

typedef struct listaTerra {   
  terra *inicio;   
  terra *fim;   
  int tamanho;   
}listaTerra;  

typedef struct parede{
  int x, y;
  struct parede *proximo;
  struct parede *anterior;
}parede;

typedef struct listaParede {   
  parede *inicio;   
  parede *fim;   
  int tamanho;   
}listaParede;  

typedef struct cristal{
  int x, y;
}cristal;

typedef struct muro{
  int x, y;
}muro;

typedef struct PLAYER{
  int x, y;
  int frame;
}PLAYER;

void player_init(PLAYER *player);

void iniciaListaTerra(listaTerra *lista);

int insListaVazTerra (listaTerra * lista, int x, int y);

int insListaFimTerra(listaTerra *lista, int x, int y);

int removListaTerra(listaTerra *lista, int x, int y);

void destruirListaTerra(listaTerra *lista);

void iniciaListaParede(listaParede *lista);

int insListaVazParede (listaParede * lista, int x, int y);

int insListaFimParede(listaParede *lista, int x, int y);

int removListaParede(listaParede *lista, int x, int y);

void destruirListaParede(listaParede *lista);

void player_update(PLAYER *player, unsigned char *key);

void player_draw(PLAYER player,unsigned char *key, SPRITESBD spritesbd);


#endif
