#ifndef __HELPER__
#define __HELPER__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_W 640
#define BUFFER_H 368


#define DISP_SCALE 2
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)


#define PLAYER_MAX_X (BUFFER_W - 2 * TILE)
#define PLAYER_MAX_Y (BUFFER_H - 2 * TILE)

#define TILE 16


void must_init(bool test, const char *description);

#endif
