#ifndef ALLEGRO_SPRITES_H
#define ALLEGRO_SPRITES_H

#include "allegroUtil.h"

#define SHIP_W 12
#define SHIP_H 13

#define SHIP_SHOT_W 2
#define SHIP_SHOT_H 9

#define LIFE_W 6
#define LIFE_H 6

extern const int ALIEN_W[];
extern const int ALIEN_H[];

#define ALIEN_BUG_W ALIEN_W[0]
#define ALIEN_BUG_H ALIEN_H[0]
#define ALIEN_ARROW_W ALIEN_W[1]
#define ALIEN_ARROW_H ALIEN_H[1]
#define ALIEN_THICCBOI_W ALIEN_W[2]
#define ALIEN_THICCBOI_H ALIEN_H[2]

#define ALIEN_SHOT_W 4
#define ALIEN_SHOT_H 4

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES 3

typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;

    // Sprites do jogador
    ALLEGRO_BITMAP* ship;
    ALLEGRO_BITMAP* ship_shot[2];
    ALLEGRO_BITMAP* life;

    // Sprites dos aliens
    ALLEGRO_BITMAP* alien[3];
    ALLEGRO_BITMAP* alien_shot;

    // Sprites dos efeitos
    ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
    ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

    ALLEGRO_BITMAP* powerup[4];
} SPRITES;

extern SPRITES sprites;

// Pega os sprites da spritesheet
ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h);

// Inicializa o Bitmap dos sprites
void sprintes_init();

// Libera o Bitmap dos sprites
void sprites_deinit();

#endif