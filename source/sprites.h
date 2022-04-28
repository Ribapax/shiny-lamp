#ifndef __SPRITES__
#define __SPRITES__

#include "helper.h"
//#include "mapas.h"
#include <allegro5/allegro.h>

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES 3

#define SHIP_W 12
#define SHIP_H 13

#define SHIP_SHOT_W 2
#define SHIP_SHOT_H 9

#define LIFE_W 6
#define LIFE_H 6

// const int ALIEN_W[] = {14, 13, 45};
// const int ALIEN_H[] = {9, 10, 27};

#define ALIEN_SHOT_W 4
#define ALIEN_SHOT_H 4

#define ALIEN_BUG_W 14
#define ALIEN_BUG_H 9
#define ALIEN_ARROW_W 13
#define ALIEN_ARROW_H 10
#define ALIEN_THICCBOI_W 45
#define ALIEN_THICCBOI_H 27

typedef struct SPRITESBD {
  ALLEGRO_BITMAP *_sheet;

  ALLEGRO_BITMAP *wall;
  ALLEGRO_BITMAP *jogador[7];
  ALLEGRO_BITMAP *jogadorDir[7];
  ALLEGRO_BITMAP *jogadorEsq[7];
  ALLEGRO_BITMAP *cristal[8];

  ALLEGRO_BITMAP *dirt;

} SPRITESBD;

typedef struct SPRITES {
  ALLEGRO_BITMAP *_sheet;

  ALLEGRO_BITMAP *ship;
  ALLEGRO_BITMAP *ship_shot[2];
  ALLEGRO_BITMAP *life;

  ALLEGRO_BITMAP *alien[3];
  ALLEGRO_BITMAP *alien_shot;

  ALLEGRO_BITMAP *explosion[EXPLOSION_FRAMES];
  ALLEGRO_BITMAP *sparks[SPARKS_FRAMES];

  ALLEGRO_BITMAP *powerup[4];
} SPRITES;


void sprite_init(SPRITESBD *spritesbd, SPRITES *sprites);

void sprites_deinit(SPRITES sprites) ;

ALLEGRO_BITMAP *sprite_grab(int x, int y, int w, int h, ALLEGRO_BITMAP *sprites);

ALLEGRO_BITMAP *sprite_grabBd(int x, int y, int w, int h, ALLEGRO_BITMAP *spritesbd);


#endif
