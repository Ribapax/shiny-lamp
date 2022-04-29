/* this is a complete copy of the source from allegro vivace's 'gameplay'
 * section.
 *
 * for gcc users, it can be compiled & run with:
 *
 * gcc game.c -o game $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5
 * allegro_audio-5 allegro_acodec-5 allegro_image-5 --libs --cflags)
 * ./game
 */

#include "estruturas.h"
#include "helper.h"
#include "mapas.h"
#include "sprites.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>


long frames;
long score;
long score_bd;

int between(int lo, int hi) { return lo + (rand() % (hi - lo)); }

float between_f(float lo, float hi) {
  return lo + ((float)rand() / (float)RAND_MAX) * (hi - lo);
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2,
             int by2) {
  if (ax1 > bx2)
    return false;
  if (ax2 < bx1)
    return false;
  if (ay1 > by2)
    return false;
  if (ay2 < by1)
    return false;

  return true;
}

// --- display ---

#define BUFFER_W 640
#define BUFFER_H 368

#define DISP_SCALE 2
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

ALLEGRO_DISPLAY *disp;
ALLEGRO_BITMAP *buffer;

void disp_init() {
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  disp = al_create_display(DISP_W, DISP_H);
  must_init(disp, "display");

  buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  must_init(buffer, "bitmap buffer");
}

void disp_deinit() {
  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
}

void disp_pre_draw() { al_set_target_bitmap(buffer); }

void disp_post_draw() {
  al_set_target_backbuffer(disp);
  al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H,
                        0);

  al_flip_display();
}

// --- keyboard ---

#define KEY_SEEN 1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init() { memset(key, 0, sizeof(key)); }

void keyboard_update(ALLEGRO_EVENT *event) {
  switch (event->type) {
  case ALLEGRO_EVENT_TIMER:
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
      key[i] &= KEY_SEEN;
    break;

  case ALLEGRO_EVENT_KEY_DOWN:
    key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
    break;
  case ALLEGRO_EVENT_KEY_UP:
    key[event->keyboard.keycode] &= KEY_RELEASED;
    break;
  }
}

// --- sprites ---

#define TILE 16


// --- audio ---

ALLEGRO_SAMPLE *sample_shot;
ALLEGRO_SAMPLE *sample_explode[2];

void audio_init() {
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(128);

  sample_shot = al_load_sample("resources/shot.flac");
  must_init(sample_shot, "shot sample");

  sample_explode[0] = al_load_sample("resources/explode1.flac");
  must_init(sample_explode[0], "explode[0] sample");
  sample_explode[1] = al_load_sample("resources/explode2.flac");
  must_init(sample_explode[1], "explode[1] sample");
}

void audio_deinit() {
  al_destroy_sample(sample_shot);
  al_destroy_sample(sample_explode[0]);
  al_destroy_sample(sample_explode[1]);
}

// --- fx ---

typedef struct FX {
  int x, y;
  int frame;
  bool spark;
  bool used;
} FX;

#define FX_N 128
FX fx[FX_N];

void fx_init() {
  for (int i = 0; i < FX_N; i++)
    fx[i].used = false;
}

void fx_add(bool spark, int x, int y) {
  if (!spark)
    al_play_sample(sample_explode[between(0, 2)], 0.75, 0, 1,
                   ALLEGRO_PLAYMODE_ONCE, NULL);

  for (int i = 0; i < FX_N; i++) {
    if (fx[i].used)
      continue;

    fx[i].x = x;
    fx[i].y = y;
    fx[i].frame = 0;
    fx[i].spark = spark;
    fx[i].used = true;
    return;
  }
}

void fx_update() {
  for (int i = 0; i < FX_N; i++) {
    if (!fx[i].used)
      continue;

    fx[i].frame++;

    if ((!fx[i].spark && (fx[i].frame == (EXPLOSION_FRAMES * 2))) ||
        (fx[i].spark && (fx[i].frame == (SPARKS_FRAMES * 2))))
      fx[i].used = false;
  }
}

void fx_draw(SPRITES sprites) {
  for (int i = 0; i < FX_N; i++) {
    if (!fx[i].used)
      continue;

    int frame_display = fx[i].frame / 2;
    ALLEGRO_BITMAP *bmp = fx[i].spark ? sprites.sparks[frame_display]
                                      : sprites.explosion[frame_display];

    int x = fx[i].x - (al_get_bitmap_width(bmp) / 2);
    int y = fx[i].y - (al_get_bitmap_height(bmp) / 2);
    al_draw_bitmap(bmp, x, y, 0);
  }
}

#define SHIP_SPEED 3
#define SHIP_MAX_X (BUFFER_W - SHIP_W)
#define SHIP_MAX_Y (BUFFER_H - SHIP_H)

typedef struct SHIP {
  int x, y;
  int shot_timer;
  int lives;
  int respawn_timer;
  int invincible_timer;
} SHIP;
SHIP ship;

void wall_draw(SPRITESBD spritesbd, listaParede lista) {
  // int espaco = TILE; // espaço no inicio da tela onde fica HUD do jogador

  parede *em_andamento;

  em_andamento = lista.inicio;
  for (int i = 1; i <= lista.tamanho; ++i) {
    al_draw_bitmap(spritesbd.wall, em_andamento->x, em_andamento->y, 0);
    em_andamento = em_andamento->proximo;
  }

  // for (int i = espaco; i < BUFFER_H; i += TILE) {
  //   for (int j = 0; j < BUFFER_W; j += TILE) {
  //     if (i == espaco || j == 0 || i == BUFFER_H - TILE || j == BUFFER_W -
  //     TILE)
  //       al_draw_bitmap(spritesbd.wall, j, i, 0);
  //     // else
  //     //     al_draw_bitmap(spritesbd.dirt, j, i, 0);
  //   }
  // }
}

typedef struct CRISTAL {
  int x, y;
  int frame;
  // bool ship;
  bool used;
} CRISTAL;

#define CRISTAL_N 760
CRISTAL cristals[CRISTAL_N];

void cristal_collide(int x, int y) {
  for (int i = 0; i < CRISTAL_N; i++) {
    if (cristals[i].x == x && cristals[i].y == y) {
      cristals[i].used = true;
      score = score + 200;
    }
  }
}

typedef struct DIRT {
  int x, y;
  // int frame;
  // bool ship;
  bool used;
} DIRT;

#define DIRTS_N 760
DIRT dirts[DIRTS_N];


void dirt_collide(int x, int y) {
  for (int i = 0; i < DIRTS_N; i++) {
    if (dirts[i].x == x && dirts[i].y == y)
      dirts[i].used = true;
  }
}

// --- aliens ---

typedef enum ALIEN_TYPE {
  ALIEN_TYPE_BUG = 0,
  ALIEN_TYPE_ARROW,
  ALIEN_TYPE_THICCBOI,
  ALIEN_TYPE_N
} ALIEN_TYPE;

typedef struct ALIEN {
  int x, y;
  ALIEN_TYPE type;
  int shot_timer;
  int blink;
  int life;
  bool used;
} ALIEN;

// --- hud ---

ALLEGRO_FONT *font;
long score_display;

void hud_init() {
  font = al_create_builtin_font();
  must_init(font, "font");

  score_display = 0;
}

void hud_deinit() { al_destroy_font(font); }

void hud_update() {
  if (frames % 2)
    return;

  for (long i = 5; i > 0; i--) {
    long diff = 1 << i;
    if (score_display <= (score - diff))
      score_display += diff;
  }
}

void hud_draw(SPRITES sprites) {
  al_draw_textf(font, al_map_rgb_f(1, 1, 1), 1, 1, 0, "%06ld", score_display);

  int spacing = LIFE_W + 1;

  for (int i = 0; i < ship.lives; i++)
    al_draw_bitmap(sprites.life, 1 + (i * spacing), 10, 0);
  // al_draw_bitmap(spritesbd.wall, 50, 10, 0);

  if (ship.lives < 0)
    al_draw_text(font, al_map_rgb_f(1, 1, 1), BUFFER_W / 2, BUFFER_H / 2,
                 ALLEGRO_ALIGN_CENTER, "G A M E  O V E R");
}

// --- main ---

int main() {

  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  must_init(queue, "queue");

  disp_init();

  audio_init();
  SPRITESBD spritesbd;
  SPRITES sprites;
  must_init(al_init_image_addon(), "image");
  sprite_init(&spritesbd, &sprites);

  hud_init();

  must_init(al_init_primitives_addon(), "primitives");

  must_init(al_install_audio(), "audio");
  must_init(al_init_acodec_addon(), "audio codecs");
  must_init(al_reserve_samples(16), "reserve samples");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  // SPRITESBD spritesbd;
  // SPRITES sprites;
  // sprites_init(spritesbd,sprites);

  PLAYER player;

  keyboard_init();
  // fx_init();
  // shots_init();
  // ship_init();
  // aliens_init();
  // stars_init();
  // dirt_init();
  //cristal_init();
  player_init(&player);
  listaParede listaP;
  listaTerra listaT;
  listaCristal listaC;
  listaPedra listaPedra;
  listaMuro listaM;
  listaQuadrado listaQ;
  listaBorboleta listaB;

  leMapa("resources/mapas/nivel7", &listaP, &listaT, &listaC,&listaPedra, &listaM,&listaQ,&listaB);

  frames = 0;
  score = 0;

  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;

  al_start_timer(timer);

  for (;;) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_TIMER:
      // fx_update();
      // shots_update();
      // stars_update();
      player_update(&player, key);
      // ship_update();
      // aliens_update();
      redraw = true;
      frames++;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    }

    if (done)
      break;

    keyboard_update(&event);

    if (redraw && al_is_event_queue_empty(queue)) {

      disp_pre_draw();
      al_clear_to_color(al_map_rgb(0, 0, 0));

      // stars_draw();
      // aliens_draw(sprites);
      // shots_draw(sprites);
      // fx_draw(sprites);
      // ship_draw(sprites);
      wall_draw(spritesbd, listaP);
      muro_draw(spritesbd, listaM);
      pedra_draw(spritesbd, listaPedra);
      dirt_draw(spritesbd, listaT);
      cristal_draw(spritesbd, listaC);
      quadrado_draw(spritesbd, listaQ);
      borboleta_draw(spritesbd, listaB);
      player_draw(player, key, spritesbd);


      hud_draw(sprites);

      disp_post_draw();
      redraw = false;
    }
  }

  sprites_deinit(sprites);
  hud_deinit();
  audio_deinit();
  disp_deinit();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}
