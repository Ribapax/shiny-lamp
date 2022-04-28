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

typedef struct muro{
  int x, y;
  struct muro *proximo;
  struct muro *anterior;
}muro;

typedef struct listaMuro {   
  muro *inicio;   
  muro *fim;   
  int tamanho;   
}listaMuro;  

typedef struct pedra{
  int x, y;
  struct pedra *proximo;
  struct pedra *anterior;
}pedra;

typedef struct listaPedra {   
  pedra *inicio;   
  pedra *fim;   
  int tamanho;   
}listaPedra;  

typedef struct cristal{
  int x, y;
  int frame;
  struct cristal *proximo;
  struct cristal *anterior;
}cristal;

typedef struct listaCristal {   
  cristal *inicio;   
  cristal *fim;   
  int tamanho;   
}listaCristal;  

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

void iniciaListaCristal(listaCristal *lista);

int insListaVazCristal (listaCristal * lista, int x, int y);

int insListaFimCristal(listaCristal *lista, int x, int y);

int removListaCristal(listaCristal *lista, int x, int y);

void destruirListaCristal(listaCristal *lista);

void iniciaListaParede(listaParede *lista);

int insListaVazParede (listaParede * lista, int x, int y);

int insListaFimParede(listaParede *lista, int x, int y);

int removListaParede(listaParede *lista, int x, int y);

void destruirListaParede(listaParede *lista);

void iniciaListaMuro(listaMuro *lista);

int insListaVazMuro (listaMuro * lista, int x, int y);

int insListaFimMuro(listaMuro *lista, int x, int y);

int removListaMuro(listaMuro *lista, int x, int y);

void destruirListaMuro(listaMuro *lista);

void iniciaListaPedra(listaPedra *lista);

int insListaVazPedra (listaPedra * lista, int x, int y);

int insListaFimPedra(listaPedra *lista, int x, int y);

int removListaPedra(listaPedra *lista, int x, int y);

void destruirListaPedra(listaPedra *lista);

void player_update(PLAYER *player, unsigned char *key);

void player_draw(PLAYER player,unsigned char *key, SPRITESBD spritesbd);

void dirt_draw(SPRITESBD spritesbd, listaTerra lista);

void muro_draw(SPRITESBD spritesbd, listaMuro lista);

void pedra_draw(SPRITESBD spritesbd, listaPedra lista);

#endif
