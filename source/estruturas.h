#ifndef __ESTRUTURAS__
#define __ESTRUTURAS__

#include "helper.h"
#include "sprites.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <stdlib.h>


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
  int dir; //1 direita 2 baixo -1 esquerda -2 cima
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
  int dir; //1 direita 2 baixo -1 esquerda -2 cima
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



int removListaCristal(listaCristal *lista, int x, int y);


int removListaTerra(listaTerra *lista, int x, int y);


void changeListaPedra(listaPedra *lista, int x, int y, int x_novo);



bool findListaCristal(listaCristal *lista, int x, int y);


bool findListaParede(listaParede *lista, int x, int y);


bool findListaPedra(listaPedra *lista, int x, int y);

bool findListaMuro(listaMuro *lista, int x, int y);

bool findListaTerra(listaTerra *lista, int x, int y);



bool posicaoLivre(int x, int y, listaParede *lista, listaTerra *listTerra,
                       listaCristal *listCristal, listaPedra *listPedra,
                       listaMuro *listMuro, listaQuadrado *listQuadrado,
                       listaBorboleta *listBorboleta, listaAmoeba *listAmoeba);


#endif
