#include "allegroUtil.h"

#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

#ifndef ASTEROIDS_LIB_H
#define ASTEROIDS_LIB_H

extern long frames;
extern long score;

// Gera um Int aleatorio entre a e b
int between(int min, int max);

// Gera um Float aleatorio entre a e b
float betweenF(float min, float max);

// Checa se dois objetos colidiram
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

#endif