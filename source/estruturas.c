
#include "estruturas.h"
#include <stdio.h>

void player_init(PLAYER *player) {
  player->x = 16;
  player->y = 32;
  player->frame = 0;
}

void player_update(PLAYER *player, unsigned char *key) {

  if (player->frame % 6 == 0) {

    if (key[ALLEGRO_KEY_LEFT])
      player->x -= 16;
    else if (key[ALLEGRO_KEY_RIGHT])
      player->x += 16;
    else if (key[ALLEGRO_KEY_UP])
      player->y -= 16;
    else if (key[ALLEGRO_KEY_DOWN])
      player->y += 16;

    if (player->x < 16)
      player->x = 16;
    if (player->y < 32)
      player->y = 32;

    if (player->x > PLAYER_MAX_X)
      player->x = PLAYER_MAX_X;
    if (player->y > PLAYER_MAX_Y)
      player->y = PLAYER_MAX_Y;

    // dirt_collide(player->x, player->y);
    // cristal_collide(player->x, player->y);

    // if(player->invincible_timer)
    //     player->invincible_timer--;
    // else
    // {
    //     if(shots_collide(true, player->x, player->y, player_W, player_H))
    //     {
    //         int x = player->x + (player_W / 2);
    //         int y = player->y + (player_H / 2);
    //         fx_add(false, x, y);
    //         fx_add(false, x+4, y+2);
    //         fx_add(false, x-2, y-4);
    //         fx_add(false, x+1, y-5);

    //         player->lives--;
    //         player->respawn_timer = 90;
    //         player->invincible_timer = 180;
    //     }
    // }

    // if(player->shot_timer)
    //     player->shot_timer--;
    // else if(key[ALLEGRO_KEY_X])
    // {
    //     int x = player->x + (player_W / 2);
    //     if(shots_add(true, false, x, player->y))
    //         player->shot_timer = 5;
    // }
  }
  player->frame++;
}

void player_draw(PLAYER player, unsigned char *key, SPRITESBD spritesbd) {

  int frame_display = (player.frame / 10) % 7;

  // if(shots[i].ship)
  if (key[ALLEGRO_KEY_LEFT])
    al_draw_bitmap(spritesbd.jogadorEsq[frame_display], player.x, player.y, 0);
  else if (key[ALLEGRO_KEY_RIGHT])
    al_draw_bitmap(spritesbd.jogadorDir[frame_display], player.x, player.y, 0);
  else
    al_draw_bitmap(spritesbd.jogador[frame_display], player.x, player.y, 0);
  // al_draw_bitmap(sprites.ship_shot[frame_display], shots[i].x, shots[i].y,
  // 0);
  /* else // alien
  {
      ALLEGRO_COLOR tint =
          frame_display
          ? al_map_rgb_f(1, 1, 1)
          : al_map_rgb_f(0.5, 0.5, 0.5)
      ;
      al_draw_tinted_bitmap(sprites.alien_shot, tint, shots[i].x, shots[i].y,
  0);
  } */
}

void dirt_draw(SPRITESBD spritesbd, listaTerra lista) {
  // int espaco = TILE;
  terra *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.dirt, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }

  // for (int i = 0; i < DIRTS_N; i++) {
  //   if (dirts[i].used == false)
  //     al_draw_bitmap(spritesbd.dirt, dirts[i].x, dirts[i].y, 0);
  // }
}

void muro_draw(SPRITESBD spritesbd, listaMuro lista) {
  muro *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.muro, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }
}

void pedra_draw(SPRITESBD spritesbd, listaPedra lista) {
  pedra *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.pedra, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }
}

void cristal_draw(SPRITESBD spritesbd, listaCristal lista) {
  // int espaco = TILE;
  int frame_display;

  cristal *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    frame_display = (em_andamento->frame / 5) % 8;

    al_draw_bitmap(spritesbd.cristal[frame_display], em_andamento->x,
                   em_andamento->y, 0);
    em_andamento->frame++;
    em_andamento = em_andamento->proximo;
  }

  // for (int i = 0; i < CRISTAL_N; i++) {
  //   if (cristals[i].used == false) {
  //     frame_display = (cristals[i].frame / 5) % 8;
  //     al_draw_bitmap(spritesbd.cristal[frame_display], cristals[i].x,
  //                    cristals[i].y, 0);
  //     cristals[i].frame++;
  //   }
  // al_draw_bitmap(spritesbd.dirt,dirts[i].x,dirts[i].y, 0);
  // }
}

void quadrado_draw(SPRITESBD spritesbd, listaQuadrado lista) {
  // int espaco = TILE;
  int frame_display;

  quadrado *em_andamento;

  em_andamento = lista.inicio;

  for (int i = 1; i <= lista.tamanho; i++) {
    frame_display = (em_andamento->frame / 5) % 4;

    al_draw_bitmap(spritesbd.quadrado[frame_display], em_andamento->x,
                   em_andamento->y, 0);
    em_andamento->frame++;
    em_andamento = em_andamento->proximo;
  }

}

void borboleta_draw(SPRITESBD spritesbd, listaBorboleta lista) {
  // int espaco = TILE;
  int frame_display;

  borboleta *em_andamento;

  em_andamento = lista.inicio;

  for (int i = 1; i <= lista.tamanho; i++) {
    frame_display = (em_andamento->frame / 5) % 4;

    al_draw_bitmap(spritesbd.borboleta[frame_display], em_andamento->x,
                   em_andamento->y, 0);
    em_andamento->frame++;
    em_andamento = em_andamento->proximo;
  }

}

void iniciaListaMuro(listaMuro *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazMuro(listaMuro *lista, int x, int y) {

  muro *novaMuro;
  if ((novaMuro = malloc(sizeof(muro))) == NULL)
    return -1;

  novaMuro->x = x;
  novaMuro->y = y;

  novaMuro->anterior = lista->inicio;
  novaMuro->proximo = lista->fim;

  lista->inicio = novaMuro;
  lista->fim = novaMuro;
  lista->tamanho++;
  return 0;
}

int insListaFimMuro(listaMuro *lista, int x, int y) {
  muro *novaMuro;
  if ((novaMuro = malloc(sizeof(muro))) == NULL)
    return -1;

  novaMuro->x = x;
  novaMuro->y = y;

  novaMuro->proximo = NULL;
  novaMuro->anterior = lista->fim;

  lista->fim->proximo = novaMuro;
  lista->fim = novaMuro;
  lista->tamanho++;

  return 0;
}

int removListaMuro(listaMuro *lista, int x, int y) {
  int pos;
  muro *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaMuro(listaMuro *lista) {
  muro *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaPedra(listaPedra *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazPedra(listaPedra *lista, int x, int y) {

  pedra *novaPedra;
  if ((novaPedra = malloc(sizeof(pedra))) == NULL)
    return -1;

  novaPedra->x = x;
  novaPedra->y = y;

  novaPedra->anterior = lista->inicio;
  novaPedra->proximo = lista->fim;

  lista->inicio = novaPedra;
  lista->fim = novaPedra;
  lista->tamanho++;
  return 0;
}

int insListaFimPedra(listaPedra *lista, int x, int y) {
  pedra *novaPedra;
  if ((novaPedra = malloc(sizeof(pedra))) == NULL)
    return -1;

  novaPedra->x = x;
  novaPedra->y = y;

  novaPedra->proximo = NULL;
  novaPedra->anterior = lista->fim;

  lista->fim->proximo = novaPedra;
  lista->fim = novaPedra;
  lista->tamanho++;

  return 0;
}

int removListaPedra(listaPedra *lista, int x, int y) {
  int pos;
  pedra *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaPedra(listaPedra *lista) {
  pedra *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaTerra(listaTerra *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazTerra(listaTerra *lista, int x, int y) {

  terra *novaTerra;
  if ((novaTerra = malloc(sizeof(terra))) == NULL)
    return -1;

  novaTerra->x = x;
  novaTerra->y = y;

  novaTerra->anterior = lista->inicio;
  novaTerra->proximo = lista->fim;

  lista->inicio = novaTerra;
  lista->fim = novaTerra;
  lista->tamanho++;
  return 0;
}

int insListaFimTerra(listaTerra *lista, int x, int y) {
  terra *novaTerra;
  if ((novaTerra = malloc(sizeof(terra))) == NULL)
    return -1;

  novaTerra->x = x;
  novaTerra->y = y;

  novaTerra->proximo = NULL;
  novaTerra->anterior = lista->fim;

  lista->fim->proximo = novaTerra;
  lista->fim = novaTerra;
  lista->tamanho++;

  return 0;
}

int removListaTerra(listaTerra *lista, int x, int y) {
  int pos;
  terra *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaTerra(listaTerra *lista) {
  terra *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaParede(listaParede *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazParede(listaParede *lista, int x, int y) {

  parede *novaParede;
  if ((novaParede = malloc(sizeof(parede))) == NULL)
    return -1;

  novaParede->x = x;
  novaParede->y = y;

  novaParede->anterior = lista->inicio;
  novaParede->proximo = lista->fim;

  lista->inicio = novaParede;
  lista->fim = novaParede;
  lista->tamanho++;
  return 0;
}

int insListaFimParede(listaParede *lista, int x, int y) {
  parede *novaParede;
  if ((novaParede = malloc(sizeof(parede))) == NULL)
    return -1;

  novaParede->x = x;
  novaParede->y = y;

  novaParede->proximo = NULL;
  novaParede->anterior = lista->fim;

  lista->fim->proximo = novaParede;
  lista->fim = novaParede;
  lista->tamanho++;

  return 0;
}

int removListaParede(listaParede *lista, int x, int y) {
  int pos;
  parede *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaParede(listaParede *lista) {
  parede *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaQuadrado(listaQuadrado *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazQuadrado(listaQuadrado *lista, int x, int y) {

  quadrado *novaQuadrado;
  if ((novaQuadrado = malloc(sizeof(quadrado))) == NULL)
    return -1;

  novaQuadrado->x = x;
  novaQuadrado->y = y;
  novaQuadrado->frame = 0;

  novaQuadrado->anterior = lista->inicio;
  novaQuadrado->proximo = lista->fim;

  lista->inicio = novaQuadrado;
  lista->fim = novaQuadrado;
  lista->tamanho++;
  return 0;
}

int insListaFimQuadrado(listaQuadrado *lista, int x, int y) {
  quadrado *novaQuadrado;
  if ((novaQuadrado = malloc(sizeof(quadrado))) == NULL)
    return -1;

  novaQuadrado->x = x;
  novaQuadrado->y = y;
  novaQuadrado->frame = 0;

  novaQuadrado->proximo = NULL;
  novaQuadrado->anterior = lista->fim;

  lista->fim->proximo = novaQuadrado;
  lista->fim = novaQuadrado;
  lista->tamanho++;

  return 0;
}

int removListaQuadrado(listaQuadrado *lista, int x, int y) {
  int pos;
  quadrado *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaQuadrado(listaQuadrado *lista) {
  quadrado *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaBorboleta(listaBorboleta *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazBorboleta(listaBorboleta *lista, int x, int y) {

  borboleta *novaBorboleta;
  if ((novaBorboleta = malloc(sizeof(borboleta))) == NULL)
    return -1;

  novaBorboleta->x = x;
  novaBorboleta->y = y;
  novaBorboleta->frame = 0;

  novaBorboleta->anterior = lista->inicio;
  novaBorboleta->proximo = lista->fim;

  lista->inicio = novaBorboleta;
  lista->fim = novaBorboleta;
  lista->tamanho++;
  return 0;
}

int insListaFimBorboleta(listaBorboleta *lista, int x, int y) {
  borboleta *novaBorboleta;
  if ((novaBorboleta = malloc(sizeof(borboleta))) == NULL)
    return -1;

  novaBorboleta->x = x;
  novaBorboleta->y = y;
  novaBorboleta->frame = 0;

  novaBorboleta->proximo = NULL;
  novaBorboleta->anterior = lista->fim;

  lista->fim->proximo = novaBorboleta;
  lista->fim = novaBorboleta;
  lista->tamanho++;

  return 0;
}

int removListaBorboleta(listaBorboleta *lista, int x, int y) {
  int pos;
  borboleta *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaBorboleta(listaBorboleta *lista) {
  borboleta *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}

void iniciaListaCristal(listaCristal *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

int insListaVazCristal(listaCristal *lista, int x, int y) {

  cristal *novaCristal;
  if ((novaCristal = malloc(sizeof(cristal))) == NULL)
    return -1;

  novaCristal->x = x;
  novaCristal->y = y;
  novaCristal->frame = 0;

  novaCristal->anterior = lista->inicio;
  novaCristal->proximo = lista->fim;

  lista->inicio = novaCristal;
  lista->fim = novaCristal;
  lista->tamanho++;
  return 0;
}

int insListaFimCristal(listaCristal *lista, int x, int y) {
  cristal *novaCristal;
  if ((novaCristal = malloc(sizeof(cristal))) == NULL)
    return -1;

  novaCristal->x = x;
  novaCristal->y = y;
  novaCristal->frame = 0;

  novaCristal->proximo = NULL;
  novaCristal->anterior = lista->fim;

  lista->fim->proximo = novaCristal;
  lista->fim = novaCristal;
  lista->tamanho++;

  return 0;
}

int removListaCristal(listaCristal *lista, int x, int y) {
  int pos;
  cristal *remov_elemento, *em_andamento;

  em_andamento = lista->inicio;
  for (int i = 1; i < lista->tamanho; ++i) {
    if (em_andamento->x == x && em_andamento->y == y)
      pos = i;
    em_andamento = em_andamento->proximo;
  }

  if (lista->tamanho == 0)
    return -1;

  if (pos == 1) { /* remoção do 1° elemento */
    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
  } else if (pos == lista->tamanho) { /* remoção do último elemento */
    remov_elemento = lista->fim;
    lista->fim->anterior->proximo = NULL;
    lista->fim = lista->fim->anterior;
  } else { /* remoção em outro lugar */
    em_andamento = lista->inicio;
    for (int i = 1; i < pos; ++i)
      em_andamento = em_andamento->proximo;
    remov_elemento = em_andamento;
    em_andamento->anterior->proximo = em_andamento->proximo;
    em_andamento->proximo->anterior = em_andamento->anterior;
  }
  // free(remov_elemento->dado);
  free(remov_elemento);
  lista->tamanho--;
  return 0;
}

void destruirListaCristal(listaCristal *lista) {
  cristal *remov_elemento;

  while (lista->tamanho > 0) {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;
    free(remov_elemento);
    lista->tamanho--;
  }
}
