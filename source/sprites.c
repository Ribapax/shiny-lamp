#include "sprites.h"

void sprite_init(SPRITESBD *spritesbd, SPRITES *sprites) {

  sprites->_sheet = al_load_bitmap("resources/spritesheet.png");
  must_init(sprites->_sheet, "spritesheet");

  spritesbd->_sheet = al_load_bitmap("resources/spritesheetBD.png");
  must_init(spritesbd->_sheet, "spritesheet");

  spritesbd->wall = sprite_grabBd(0, 48, TILE, TILE,spritesbd->_sheet);

  spritesbd->dirt = sprite_grabBd(48, 48, TILE, TILE,spritesbd->_sheet);
  spritesbd->muro = sprite_grabBd(32, 48, TILE, TILE,spritesbd->_sheet);
  spritesbd->pedra = sprite_grabBd(80, 48, TILE, TILE,spritesbd->_sheet);

  spritesbd->quadrado[0] = sprite_grabBd(80, 64, TILE, TILE,spritesbd->_sheet);
  spritesbd->quadrado[1] = sprite_grabBd(80, 80, TILE, TILE,spritesbd->_sheet);
  spritesbd->quadrado[2] = sprite_grabBd(80, 96, TILE, TILE,spritesbd->_sheet);
  spritesbd->quadrado[3] = sprite_grabBd(80, 112, TILE, TILE,spritesbd->_sheet);
  
  spritesbd->borboleta[0] = sprite_grabBd(96, 64, TILE, TILE,spritesbd->_sheet);
  spritesbd->borboleta[1] = sprite_grabBd(96, 80, TILE, TILE,spritesbd->_sheet);
  spritesbd->borboleta[2] = sprite_grabBd(96, 96, TILE, TILE,spritesbd->_sheet);
  spritesbd->borboleta[3] = sprite_grabBd(96, 112, TILE, TILE,spritesbd->_sheet);
  
  spritesbd->jogador[0] = sprite_grabBd(0, 0, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogador[1] = sprite_grabBd(16, 0, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogador[2] = sprite_grabBd(32, 0, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogador[3] = sprite_grabBd(48, 0, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogador[4] = sprite_grabBd(64, 0, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogador[5] = sprite_grabBd(80, 0, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogador[6] = sprite_grabBd(96, 0, TILE, TILE,spritesbd->_sheet);

  spritesbd->jogadorEsq[0] = sprite_grabBd(0, 16, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorEsq[1] = sprite_grabBd(16, 16, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorEsq[2] = sprite_grabBd(32, 16, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorEsq[3] = sprite_grabBd(48, 16, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorEsq[4] = sprite_grabBd(64, 16, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorEsq[5] = sprite_grabBd(80, 16, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorEsq[6] = sprite_grabBd(96, 16, TILE, TILE,spritesbd->_sheet);

  spritesbd->jogadorDir[0] = sprite_grabBd(0, 32, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorDir[1] = sprite_grabBd(16, 32, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorDir[2] = sprite_grabBd(32, 32, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorDir[3] = sprite_grabBd(48, 32, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorDir[4] = sprite_grabBd(64, 32, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorDir[5] = sprite_grabBd(80, 32, TILE, TILE,spritesbd->_sheet);
  spritesbd->jogadorDir[6] = sprite_grabBd(96, 32, TILE, TILE,spritesbd->_sheet);

  spritesbd->cristal[0] = sprite_grabBd(0, 64, TILE, TILE,spritesbd->_sheet);
  spritesbd->cristal[1] = sprite_grabBd(0, 80, TILE, TILE,spritesbd->_sheet);
  spritesbd->cristal[2] = sprite_grabBd(0, 96, TILE, TILE,spritesbd->_sheet);
  spritesbd->cristal[3] = sprite_grabBd(0, 112, TILE, TILE,spritesbd->_sheet);
  spritesbd->cristal[4] = sprite_grabBd(16, 64, TILE, TILE,spritesbd->_sheet);
  spritesbd->cristal[5] = sprite_grabBd(16, 80, TILE, TILE,spritesbd->_sheet);
  spritesbd->cristal[6] = sprite_grabBd(16, 96, TILE, TILE,spritesbd->_sheet);
  spritesbd->cristal[7] = sprite_grabBd(16, 112, TILE, TILE,spritesbd->_sheet);

  sprites->ship = sprite_grab(0, 0, SHIP_W, SHIP_H,sprites->_sheet);

  sprites->life = sprite_grab(0, 14, LIFE_W, LIFE_H,sprites->_sheet);

  sprites->ship_shot[0] = sprite_grab(13, 0, SHIP_SHOT_W, SHIP_SHOT_H,sprites->_sheet);
  sprites->ship_shot[1] = sprite_grab(16, 0, SHIP_SHOT_W, SHIP_SHOT_H,sprites->_sheet);

  sprites->alien[0] = sprite_grab(19, 0, ALIEN_BUG_W, ALIEN_BUG_H,sprites->_sheet);
  sprites->alien[1] = sprite_grab(19, 10, ALIEN_ARROW_W, ALIEN_ARROW_H,sprites->_sheet);
  sprites->alien[2] = sprite_grab(0, 21, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H,sprites->_sheet);

  sprites->alien_shot = sprite_grab(13, 10, ALIEN_SHOT_W, ALIEN_SHOT_H,sprites->_sheet);

  sprites->explosion[0] = sprite_grab(33, 10, 9, 9,sprites->_sheet);
  sprites->explosion[1] = sprite_grab(43, 9, 11, 11,sprites->_sheet);
  sprites->explosion[2] = sprite_grab(46, 21, 17, 18,sprites->_sheet);
  sprites->explosion[3] = sprite_grab(46, 40, 17, 17,sprites->_sheet);

  sprites->sparks[0] = sprite_grab(34, 0, 10, 8,sprites->_sheet);
  sprites->sparks[1] = sprite_grab(45, 0, 7, 8,sprites->_sheet);
  sprites->sparks[2] = sprite_grab(54, 0, 9, 8,sprites->_sheet);

  sprites->powerup[0] = sprite_grab(0, 49, 9, 12,sprites->_sheet);
  sprites->powerup[1] = sprite_grab(10, 49, 9, 12,sprites->_sheet);
  sprites->powerup[2] = sprite_grab(20, 49, 9, 12,sprites->_sheet);
  sprites->powerup[3] = sprite_grab(30, 49, 9, 12,sprites->_sheet);
}


ALLEGRO_BITMAP *sprite_grab(int x, int y, int w, int h, ALLEGRO_BITMAP *sprites) {
  ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites, x, y, w, h);
  must_init(sprite, "sprite grab");
  return sprite;
}

ALLEGRO_BITMAP *sprite_grabBd(int x, int y, int w, int h, ALLEGRO_BITMAP *spritesbd) {
  ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(spritesbd, x, y, w, h);
  must_init(sprite, "sprite grab");
  return sprite;
}


void sprites_deinit(SPRITES sprites) {

  al_destroy_bitmap(sprites.ship);

  al_destroy_bitmap(sprites.ship_shot[0]);
  al_destroy_bitmap(sprites.ship_shot[1]);

  al_destroy_bitmap(sprites.alien[0]);
  al_destroy_bitmap(sprites.alien[1]);
  al_destroy_bitmap(sprites.alien[2]);

  al_destroy_bitmap(sprites.sparks[0]);
  al_destroy_bitmap(sprites.sparks[1]);
  al_destroy_bitmap(sprites.sparks[2]);

  al_destroy_bitmap(sprites.explosion[0]);
  al_destroy_bitmap(sprites.explosion[1]);
  al_destroy_bitmap(sprites.explosion[2]);
  al_destroy_bitmap(sprites.explosion[3]);

  al_destroy_bitmap(sprites.powerup[0]);
  al_destroy_bitmap(sprites.powerup[1]);
  al_destroy_bitmap(sprites.powerup[2]);
  al_destroy_bitmap(sprites.powerup[3]);

  al_destroy_bitmap(sprites._sheet);
}

