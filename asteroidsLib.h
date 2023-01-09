#ifndef ASTEROIDS_LIB_H
#define ASTEROIDS_LIB_H

#include "allegroUtil.h"
#include "allegroSprites.h"
#include "allegroFx.h"
#include "allegroAudio.h"
#include "allegroKeyboard.h"
#include "allegroDisplay.h"

#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)
#define SHOTS_N 128

#define SHIP_SPEED 3
#define SHIP_MAX_X (BUFFER_W - SHIP_W)
#define SHIP_MAX_Y (BUFFER_H - SHIP_H)

#define ALIENS_N 16

#define STARS_N ((BUFFER_W/2)-1)

extern long frames;
extern long score;
extern long score_display;

typedef struct STAR
{
    float y;
    float speed;
} STAR;

typedef struct SHOT
{
    int x, y;
    int dx, dy;
    int frame;
    bool ship; // Se o tiro eh do jogador
    bool used; 
} SHOT;

typedef struct SHIP
{
    int x, y;
    int shot_timer;
    int lives;
    int respawn_timer;
    int invincible_timer;
}SHIP;

typedef enum ALIEN_TYPE
{
    ALIEN_TYPE_BUG = 0,
    ALIEN_TYPE_ARROW,
    ALIEN_TYPE_THICCBOI,
    ALIEN_TYPE_N
} ALIEN_TYPE;

typedef struct ALIEN
{
    int x, y;
    ALIEN_TYPE type;
    int shot_timer;
    int blink;
    int life;
    bool used;
} ALIEN;


extern SHIP ship;
extern SHOT shots[SHOTS_N];
extern ALIEN aliens[ALIENS_N];
extern STAR stars[STARS_N];

// Gera um Int aleatorio entre a e b
int between(int min, int max);

// Gera um Float aleatorio entre a e b
float betweenF(float min, float max);

// Checa se dois objetos colidiram
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

void shots_init();

bool shots_add(bool ship, bool straight, int x, int y);

void shots_update();

bool shots_collide(bool ship, int x, int y, int w, int h);

void shots_draw();

void ship_init();

void ship_update();

void ship_draw();

void aliens_init();

void aliens_update();

void aliens_draw();

void stars_init();

void stars_update();

void stars_draw();

void hud_init();

void hud_deinit();

void hud_update();

void hud_draw();


#endif