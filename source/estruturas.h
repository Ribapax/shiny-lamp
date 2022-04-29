#ifndef __ESTRUTURAS__
#define __ESTRUTURAS__

#include "helper.h"
#include "sprites.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
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

typedef struct terra {
  int x, y;
  struct terra *proximo;
  struct terra *anterior;
} terra;

typedef struct listaTerra {
  terra *inicio;
  terra *fim;
  int tamanho;
} listaTerra;

typedef struct muro {
  int x, y;
  struct muro *proximo;
  struct muro *anterior;
} muro;

typedef struct listaMuro {
  muro *inicio;
  muro *fim;
  int tamanho;
} listaMuro;

typedef struct pedra {
  int x, y;
  struct pedra *proximo;
  struct pedra *anterior;
} pedra;

typedef struct listaPedra {
  pedra *inicio;
  pedra *fim;
  int tamanho;
} listaPedra;

typedef struct cristal {
  int x, y;
  int frame;
  struct cristal *proximo;
  struct cristal *anterior;
} cristal;

typedef struct listaCristal {
  cristal *inicio;
  cristal *fim;
  int tamanho;
} listaCristal;

typedef struct quadrado {
  int x, y;
  int frame;
  struct quadrado *proximo;
  struct quadrado *anterior;
} quadrado;

typedef struct listaQuadrado {
  quadrado *inicio;
  quadrado *fim;
  int tamanho;
} listaQuadrado;

typedef struct borboleta {
  int x, y;
  int frame;
  struct borboleta *proximo;
  struct borboleta *anterior;
} borboleta;

typedef struct listaBorboleta {
  borboleta *inicio;
  borboleta *fim;
  int tamanho;
} listaBorboleta;

typedef struct amoeba {
  int x, y;
  int frame;
  struct amoeba *proximo;
  struct amoeba *anterior;
} amoeba;

typedef struct listaAmoeba {
  amoeba *inicio;
  amoeba *fim;
  int tamanho;
} listaAmoeba;

typedef struct parede {
  int x, y;
  struct parede *proximo;
  struct parede *anterior;
} parede;

typedef struct listaParede {
  parede *inicio;
  parede *fim;
  int tamanho;
} listaParede;

typedef struct PLAYER {
  int x, y;
  int frame;
} PLAYER;

void player_init(PLAYER *player, int x, int y);

void iniciaListaTerra(listaTerra *lista);

int insListaVazTerra(listaTerra *lista, int x, int y);

int insListaFimTerra(listaTerra *lista, int x, int y);

int removListaTerra(listaTerra *lista, int x, int y);

void destruirListaTerra(listaTerra *lista);

void iniciaListaCristal(listaCristal *lista);

int insListaVazCristal(listaCristal *lista, int x, int y);

int insListaFimCristal(listaCristal *lista, int x, int y);

int removListaCristal(listaCristal *lista, int x, int y);

void destruirListaCristal(listaCristal *lista);

void iniciaListaParede(listaParede *lista);

int insListaVazParede(listaParede *lista, int x, int y);

int insListaFimParede(listaParede *lista, int x, int y);

int removListaParede(listaParede *lista, int x, int y);

void destruirListaParede(listaParede *lista);

void iniciaListaMuro(listaMuro *lista);

int insListaVazMuro(listaMuro *lista, int x, int y);

int insListaFimMuro(listaMuro *lista, int x, int y);

int removListaMuro(listaMuro *lista, int x, int y);

void destruirListaMuro(listaMuro *lista);

void iniciaListaPedra(listaPedra *lista);

int insListaVazPedra(listaPedra *lista, int x, int y);

int insListaFimPedra(listaPedra *lista, int x, int y);

int removListaPedra(listaPedra *lista, int x, int y);

void destruirListaPedra(listaPedra *lista);

void iniciaListaQuadrado(listaQuadrado *lista);

int insListaVazQuadrado(listaQuadrado *lista, int x, int y);

int insListaFimQuadrado(listaQuadrado *lista, int x, int y);

int removListaQuadrado(listaQuadrado *lista, int x, int y);

void destruirListaQuadrado(listaQuadrado *lista);

void iniciaListaAmoeba(listaAmoeba *lista);

int insListaVazAmoeba(listaAmoeba *lista, int x, int y);

int insListaFimAmoeba(listaAmoeba *lista, int x, int y);

int removListaAmoeba(listaAmoeba *lista, int x, int y);

void destruirListaAmoeba(listaAmoeba *lista);

void iniciaListaBorboleta(listaBorboleta *lista);

int insListaVazBorboleta(listaBorboleta *lista, int x, int y);

int insListaFimBorboleta(listaBorboleta *lista, int x, int y);

int removListaBorboleta(listaBorboleta *lista, int x, int y);

void destruirListaBorboleta(listaBorboleta *lista);

void player_update(PLAYER *player, unsigned char *key, listaParede *lista,
                   listaTerra *listTerra, listaCristal *listCristal,
                   listaPedra *listPedra, listaMuro *listMuro,
                   listaQuadrado *listQuadrado, listaBorboleta *listBorboleta,
                   listaAmoeba *listAmoeba,ALLEGRO_SAMPLE *moeda);

void player_draw(PLAYER player, unsigned char *key, SPRITESBD spritesbd);

void dirt_draw(SPRITESBD spritesbd, listaTerra lista);

void muro_draw(SPRITESBD spritesbd, listaMuro lista);

void pedra_draw(SPRITESBD spritesbd, listaPedra lista);

void cristal_draw(SPRITESBD spritesbd, listaCristal lista);

void quadrado_draw(SPRITESBD spritesbd, listaQuadrado lista);

void borboleta_draw(SPRITESBD spritesbd, listaBorboleta lista);

void amoeba_draw(SPRITESBD spritesbd, listaAmoeba lista);

void wall_draw(SPRITESBD spritesbd, listaParede lista);

bool findListaMuro(listaMuro *lista, int x, int y);

bool findListaPedra(listaPedra *lista, int x, int y);

bool findListaTerra(listaTerra *lista, int x, int y);

bool findListaCristal(listaCristal *lista, int x, int y);

void pedra_update(PLAYER *player, listaParede *lista, listaTerra *listTerra,
                  listaCristal *listCristal, listaPedra *listPedra,
                  listaMuro *listMuro, listaQuadrado *listQuadrado,
                  listaBorboleta *listBorboleta, listaAmoeba *listAmoeba);

#endif
