
#include "audio.h"
#include "estruturas.h"
#include "help.h"
#include "helper.h"
#include "hud.h"
#include "mapas.h"
#include "sprites.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

long frames;
int score = 0;
long score_bd;

int between(int lo, int hi) { return lo + (rand() % (hi - lo)); }

float between_f(float lo, float hi) {
  return lo + ((float)rand() / (float)RAND_MAX) * (hi - lo);
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

void salvaScore(int score) {
  FILE *arq;

  arq = fopen("resources/score.txt", "w");

  if (!arq) {
    perror("Erro ao abrir arquivo");
    exit(1);
  }
  fprintf(arq, "%d", score);

  fclose(arq);
}

void lastScore(int *score) {
  FILE *arq;

  arq = fopen("resources/score.txt", "r");

  if (!arq) {
    perror("Erro ao abrir arquivo");
    exit(1);
  }
  fscanf(arq, "%d", score);

  fclose(arq);
}

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

// --- main ---

int main() {

  int nivel = 1;
  int mouse_x, mouse_y;
  int ultimo_score;
  bool carregaMapa = true;
  bool flagHelp = false;
  bool flagOver = false;

  must_init(al_init(), "allegro");

  must_init(al_install_keyboard(), "keyboard");
  must_init(al_install_mouse(), "mouse");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  must_init(queue, "queue");

  disp_init();

  ALLEGRO_SAMPLE *moeda = audio_init();

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
  al_register_event_source(queue, al_get_mouse_event_source());

  PLAYER player;
  player.lives = 3;
  player.cristnec = 5;
  player.pont = 100;

  keyboard_init();

  listaParede listaP;
  listaTerra listaT;
  listaCristal listaC;
  listaPedra listaPedra;
  listaMuro listaM;
  listaQuadrado listaQ;
  listaBorboleta listaB;
  listaAmoeba listaA;
  porta port;

  frames = 0;
  score = 0;
  lastScore(&ultimo_score);

  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;

  al_start_timer(timer);

  for (;;) {

    if (carregaMapa) {
      switch (nivel) {
      case 1:
        leMapa("resources/mapas/nivel1", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 2:
        leMapa("resources/mapas/nivel2", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 3:
        leMapa("resources/mapas/nivel3", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 4:
        leMapa("resources/mapas/nivel4", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 5:
        leMapa("resources/mapas/nivel5", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 6:
        leMapa("resources/mapas/nivel6", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 7:
        leMapa("resources/mapas/nivel7", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 8:
        leMapa("resources/mapas/nivel8", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 9:
        leMapa("resources/mapas/nivel9", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      case 10:
        leMapa("resources/mapas/nivel10", &player, &listaP, &listaT, &listaC,
               &listaPedra, &listaM, &listaQ, &listaB, &listaA, &port);
        break;
      }
      carregaMapa = false;
    }

    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_TIMER:

      if (!flagHelp) {

        player_update(&player, key, &listaP, &listaT, &listaC, &listaPedra,
                      &listaM, &listaQ, &listaB, &listaA, moeda, &score,&nivel,&carregaMapa, port);
        pedra_update(&player, &listaP, &listaT, &listaC, &listaPedra, &listaM,
                     &listaQ, &listaB, &listaA, &flagOver);
        cristal_update(&player, &listaP, &listaT, &listaC, &listaPedra, &listaM,
                       &listaQ, &listaB, &listaA, &flagOver);
        quadrado_update(&player, &listaP, &listaT, &listaC, &listaPedra,
                        &listaM, &listaQ, &listaB, &listaA, &flagOver);
        borboleta_update(&player, &listaP, &listaT, &listaC, &listaPedra,
                         &listaM, &listaQ, &listaB, &listaA , &flagOver);

        if (flagOver && player.lives > 0) {
          player.lives--;
          carregaMapa = true;
          flagOver = false;
        } else if (player.lives == 0) {
          done = true;
        }
      }

      frames++;
      redraw = true;
      break;
    case ALLEGRO_EVENT_MOUSE_AXES:
      mouse_x = event.mouse.x /16;
      mouse_y = event.mouse.y /16;
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
      al_clear_to_color(al_map_rgb(25, 29, 25));

      wall_draw(spritesbd, listaP);
      muro_draw(spritesbd, listaM);
      pedra_draw(spritesbd, listaPedra);
      dirt_draw(spritesbd, listaT);
      cristal_draw(spritesbd, listaC);
      quadrado_draw(spritesbd, listaQ);
      borboleta_draw(spritesbd, listaB);
      amoeba_draw(spritesbd, listaA);
      player_draw(player, key, spritesbd);
      porta_draw(spritesbd, port, player);
      hud_draw(font, &player, &spritesbd, score);

      if (flagHelp) {
        help_draw(font, ultimo_score);
      }

      disp_post_draw();
      redraw = false;
    }
    if (frames % 10 == 0) {
      if (key[ALLEGRO_KEY_H] || key[ALLEGRO_KEY_F1]) {
        if (flagHelp)
          flagHelp = false;
        else
          flagHelp = true;
      }

      if (key[ALLEGRO_KEY_PGUP]) {
        nivel--;
        if (nivel < 1)
          nivel = 1;
        carregaMapa = true;
      }

      if (key[ALLEGRO_KEY_T]) {
        if (listaC.inicio != NULL) {
          player.x = listaC.inicio->x;
          player.y = listaC.inicio->y;
        }
      }

      if (key[ALLEGRO_KEY_PGDN]) {
        nivel++;
        if (nivel > 10)
          nivel = 10;
        carregaMapa = true;
      }
    }

    if (key[ALLEGRO_KEY_ESCAPE]) {
      done = true;
    }
  }

  salvaScore(score);
  sprites_deinit(sprites);
  hud_deinit();
  audio_deinit(moeda);
  disp_deinit();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  // destruirListaAmoeba()
  destruirListaParede(&listaP);
  destruirListaTerra(&listaT);
  destruirListaCristal(&listaC);
  destruirListaPedra(&listaPedra);
  destruirListaMuro(&listaM);
  destruirListaQuadrado(&listaQ);
  destruirListaBorboleta(&listaB);
  destruirListaAmoeba(&listaA);

  return 0;
}
