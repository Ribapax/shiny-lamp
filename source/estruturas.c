
#include "estruturas.h"


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
  for (int i = 1; i < lista->tamanho; ++i){
    if(em_andamento->x ==x && em_andamento->y ==y)
      pos =i;
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

void destruirListaTerra(listaTerra *lista){ 
  terra *remov_elemento;

  while(lista->tamanho > 0)  {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;  
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
  for (int i = 1; i < lista->tamanho; ++i){
    if(em_andamento->x ==x && em_andamento->y ==y)
      pos =i;
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

void destruirListaParede(listaParede *lista){ 
  parede *remov_elemento;

  while(lista->tamanho > 0)  {

    remov_elemento = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    if (lista->inicio == NULL)
      lista->fim = NULL;
    else
      lista->inicio->anterior = NULL;  
  }

}   
