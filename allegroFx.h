#ifndef ALLLEGRO_FX_H
#define ALLLEGRO_FX_H

#include "allegroUtil.h"
#include "asteroidsLib.h"
#include "allegroAudio.h"
#include "allegroDisplay.h"

#define FX_N 128

typedef struct FX
{
    int x, y;
    int frame;
    bool spark;
    bool used;
} FX;

extern FX fx[FX_N];

// Inicializa a estrutura de efeitos
void fx_init();

// Adiciona um efeito
void fx_add(bool spark, int x, int y);

void fx_update();

void fx_draw();

#endif
