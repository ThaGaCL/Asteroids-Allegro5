#include "asteroidsLib.h"


long frames;
long score;
SHOT shots[SHOTS_N];
SHIP ship;
ALIEN aliens[ALIENS_N];
STAR stars[STARS_N];

ALLEGRO_FONT* font;
long score_display;

int between(int min, int max)
{
    return (rand() % (max - min)) + min;
}

float betweenf(float min, float max)
{
    return ((float)rand() / (float)RAND_MAX) * (max-min) + min;
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
 
    if((ax1 > bx2) || (ax2 < bx1) || (ay1 > by2) || (ay2 < by1))
        return false;

    return true;
}


void shots_init()
{
    for(int i = 0; i < SHOTS_N; i++)
        shots[i].used = false;
}

bool shots_add(bool ship, bool straight, int x, int y)
{
    al_play_sample(
        sample_shot,
        0.3,
        0,
        ship ? 1.0 : betweenf(1.5, 1.6),
        ALLEGRO_PLAYMODE_ONCE,
        NULL
    );

    for(int i = 0; i < SHOTS_N; i++)
    {
        if(shots[i].used)
            continue;

        shots[i].ship = ship;

        if(ship)
        {
            shots[i].x = x - (SHIP_SHOT_W / 2);
            shots[i].y = y;
        }
        else // alien
        {
            shots[i].x = x - (ALIEN_SHOT_W / 2);
            shots[i].y = y - (ALIEN_SHOT_H / 2);

            if(straight)
            {
                shots[i].dx = 0;
                shots[i].dy = 2;
            }
            else
            {

                shots[i].dx = between(-2, 2);
                shots[i].dy = between(-2, 2);
            }

            // if the shot has no speed, don't bother
            if(!shots[i].dx && !shots[i].dy)
                return true;

            shots[i].frame = 0;
        }

        shots[i].frame = 0;
        shots[i].used = true;

        return true;
    }
    return false;
}

void shots_update()
{
    for(int i = 0; i < SHOTS_N; i++)
    {
        if(!shots[i].used)
            continue;

        if(shots[i].ship)
        {
            shots[i].y -= 5;

            if(shots[i].y < -SHIP_SHOT_H)
            {
                shots[i].used = false;
                continue;
            }
        }
        else // alien
        {
            shots[i].x += shots[i].dx;
            shots[i].y += shots[i].dy;

            if((shots[i].x < -ALIEN_SHOT_W)
            || (shots[i].x > BUFFER_W)
            || (shots[i].y < -ALIEN_SHOT_H)
            || (shots[i].y > BUFFER_H)
            ) {
                shots[i].used = false;
                continue;
            }
        }

        shots[i].frame++;
    }
}

bool shots_collide(bool ship, int x, int y, int w, int h)
{
    for(int i = 0; i < SHOTS_N; i++)
    {
        if(!shots[i].used)
            continue;

        // don't collide with one's own shots
        if(shots[i].ship == ship)
            continue;

        int sw, sh;
        if(ship)
        {
            sw = ALIEN_SHOT_W;
            sh = ALIEN_SHOT_H;
        }
        else
        {
            sw = SHIP_SHOT_W;
            sh = SHIP_SHOT_H;
        }

        if(collide(x, y, x+w, y+h, shots[i].x, shots[i].y, shots[i].x+sw, shots[i].y+sh))
        {
            fx_add(true, shots[i].x + (sw / 2), shots[i].y + (sh / 2));
            shots[i].used = false;
            return true;
        }
    }

    return false;
}

void shots_draw()
{
    for(int i = 0; i < SHOTS_N; i++)
    {
        if(!shots[i].used)
            continue;

        int frame_display = (shots[i].frame / 2) % 2;

        if(shots[i].ship)
            al_draw_bitmap(sprites.ship_shot[frame_display], shots[i].x, shots[i].y, 0);
        else // alien
        {
            ALLEGRO_COLOR tint =
                frame_display
                ? al_map_rgb_f(1, 1, 1)
                : al_map_rgb_f(0.5, 0.5, 0.5)
            ;
            al_draw_tinted_bitmap(sprites.alien_shot, tint, shots[i].x, shots[i].y, 0);
        }
    }
}

void ship_init()
{
    ship.x = (BUFFER_W / 2) - (SHIP_W / 2);
    ship.y = (BUFFER_H / 2) - (SHIP_H / 2);
    ship.shot_timer = 0;
    ship.lives = 3;
    ship.respawn_timer = 0;
    ship.invincible_timer = 120;
}

void ship_update()
{
    if(ship.lives < 0)
        return;

    if(ship.respawn_timer)
    {
        ship.respawn_timer--;
        return;
    }

    if(key[ALLEGRO_KEY_LEFT])
        ship.x -= SHIP_SPEED;
    if(key[ALLEGRO_KEY_RIGHT])
        ship.x += SHIP_SPEED;
    if(key[ALLEGRO_KEY_UP])
        ship.y -= SHIP_SPEED;
    if(key[ALLEGRO_KEY_DOWN])
        ship.y += SHIP_SPEED;

    if(ship.x < 0)
        ship.x = 0;
    if(ship.y < 0)
        ship.y = 0;

    if(ship.x > SHIP_MAX_X)
        ship.x = SHIP_MAX_X;
    if(ship.y > SHIP_MAX_Y)
        ship.y = SHIP_MAX_Y;

    if(ship.invincible_timer)
        ship.invincible_timer--;
    else
    {
        if(shots_collide(true, ship.x, ship.y, SHIP_W, SHIP_H))
        {
            int x = ship.x + (SHIP_W / 2);
            int y = ship.y + (SHIP_H / 2);
            fx_add(false, x, y);
            fx_add(false, x+4, y+2);
            fx_add(false, x-2, y-4);
            fx_add(false, x+1, y-5);

            ship.lives--;
            ship.respawn_timer = 90;
            ship.invincible_timer = 180;
        }
    }

    if(ship.shot_timer)
        ship.shot_timer--;
    else if(key[ALLEGRO_KEY_X])
    {
        int x = ship.x + (SHIP_W / 2);
        if(shots_add(true, false, x, ship.y))
            ship.shot_timer = 5;
    }
}

void ship_draw()
{
    if(ship.lives < 0)
        return;
    if(ship.respawn_timer)
        return;
    if(((ship.invincible_timer / 2) % 3) == 1)
        return;
    
    al_draw_bitmap(sprites.ship, ship.x, ship.y, 0);
}

void aliens_init()
{
    for(int i = 0; i < ALIENS_N; i++)
        aliens[i].used = false;
}

void aliens_update()
{
    int new_quota =
        (frames % 120)
        ? 0
        : between(2, 4)
    ;
    int new_x = between(10, BUFFER_W-50);

    for(int i = 0; i < ALIENS_N; i++)
    {
        if(!aliens[i].used)
        {
            // if this alien is unused, should it spawn?
            if(new_quota > 0)
            {
                new_x += between(40, 80);
                if(new_x > (BUFFER_W - 60))
                    new_x -= (BUFFER_W - 60);

                aliens[i].x = new_x;

                aliens[i].y = between(-40, -30);
                aliens[i].type = between(0, ALIEN_TYPE_N-1);
                aliens[i].shot_timer = between(1, 99);
                aliens[i].blink = 0;
                aliens[i].used = true;

                switch(aliens[i].type)
                {
                    case ALIEN_TYPE_BUG:
                        aliens[i].life = 4;
                        break;
                    case ALIEN_TYPE_ARROW:
                        aliens[i].life = 2;
                        break;
                    case ALIEN_TYPE_THICCBOI:
                        aliens[i].life = 12;
                        break;
                }

                new_quota--;
            }
            continue;
        }

        switch(aliens[i].type)
        {
            case ALIEN_TYPE_BUG:
                if(frames % 2)
                    aliens[i].y++;
                break;

            case ALIEN_TYPE_ARROW:
                aliens[i].y++;
                break;

            case ALIEN_TYPE_THICCBOI:
                if(!(frames % 4))
                    aliens[i].y++;
                break;
        }

        if(aliens[i].y >= BUFFER_H)
        {
            aliens[i].used = false;
            continue;
        }

        if(aliens[i].blink)
            aliens[i].blink--;

        if(shots_collide(false, aliens[i].x, aliens[i].y, ALIEN_W[aliens[i].type], ALIEN_H[aliens[i].type]))
        {
            aliens[i].life--;
            aliens[i].blink = 4;
        }

        int cx = aliens[i].x + (ALIEN_W[aliens[i].type] / 2);
        int cy = aliens[i].y + (ALIEN_H[aliens[i].type] / 2);

        if(aliens[i].life <= 0)
        {
            fx_add(false, cx, cy);

            switch(aliens[i].type)
            {
                case ALIEN_TYPE_BUG:
                    score += 200;
                    break;

                case ALIEN_TYPE_ARROW:
                    score += 150;
                    break;

                case ALIEN_TYPE_THICCBOI:
                    score += 800;
                    fx_add(false, cx-10, cy-4);
                    fx_add(false, cx+4, cy+10);
                    fx_add(false, cx+8, cy+8);
                    break;
            }

            aliens[i].used = false;
            continue;
        }

        aliens[i].shot_timer--;
        if(aliens[i].shot_timer == 0)
        {
            switch(aliens[i].type)
            {
                case ALIEN_TYPE_BUG:
                    shots_add(false, false, cx, cy);
                    aliens[i].shot_timer = 150;
                    break;
                case ALIEN_TYPE_ARROW:
                    shots_add(false, true, cx, aliens[i].y);
                    aliens[i].shot_timer = 80;
                    break;
                case ALIEN_TYPE_THICCBOI:
                    shots_add(false, true, cx-5, cy);
                    shots_add(false, true, cx+5, cy);
                    shots_add(false, true, cx-5, cy + 8);
                    shots_add(false, true, cx+5, cy + 8);
                    aliens[i].shot_timer = 200;
                    break;
            }
        }
    }
}

void aliens_draw()
{
    for(int i = 0; i < ALIENS_N; i++)
    {
        if(!aliens[i].used)
            continue;
        if(aliens[i].blink > 2)
            continue;

        al_draw_bitmap(sprites.alien[aliens[i].type], aliens[i].x, aliens[i].y, 0);
    }
}

void stars_init()
{
    for (int i = 0; i < STARS_N; i++)
    {
        stars[i].y = betweenf(0, 240);
        stars[i].speed = betweenf(0.1, 1);
    }
}

void stars_update()
{
    for (int i = 0; i < STARS_N; i++)
    {
        stars[i].y += stars[i].speed;
        if(stars[i].y >= BUFFER_H)
        {
            stars[i].y = 0;
            stars[i].speed = betweenf(0.1,1);
        }
    }
    
}

void stars_draw()
{
    float star_x = 1;
    for (int i = 0; i < STARS_N; i++)
    {
        float l = stars[i].speed *0.8;
        al_draw_pixel(star_x, stars[i].y, al_map_rgb_f(l, l, l));
        star_x += 2;
    }
}

void hud_init()
{
    font = al_create_builtin_font();
    mustInit(font, "font"); 

    score_display = 0;
}

void hud_deinit()
{
    al_destroy_font(font);
}

void hud_update()
{
    if(frames % 2)
        return;
    
    for(long i = 5; i>0; i--)
    {
        long diff = 1 << i;
        if(score_display <= (score - diff))
            score_display += diff;
    }
}

void hud_draw()
{
    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 1, 1, 0, "%06ld", score_display); 

    int spacing = LIFE_W + 1;
    for (int i = 0; i < ship.lives; i++)
        al_draw_bitmap(sprites.life, 1 + (i * spacing), 10, 0);
    
    if(ship.lives < 0)
    {
        al_draw_text(font, al_map_rgb_f(1, 1, 1), BUFFER_W/2, BUFFER_H/2, ALLEGRO_ALIGN_CENTRE, "G A M E  O V E R ");
    }
    
}