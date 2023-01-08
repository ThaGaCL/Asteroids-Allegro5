#include "asteroidsLib.h"


long frames;
long score;
SHOT shots[SHOTS_N];

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

bool shots_add(int x, int y, bool ship, bool straight)
{
    al_play_sample(sample_shot, 0.3, 0, ship ? 1.0 : betweenf(1.5,1.6), ALLEGRO_PLAYMODE_ONCE, NULL);

    for(int i = 0; i < SHOTS_N; i++)
    {
            if(shots[i].used)
                continue;
            
            shots[i].ship = ship;

            if(ship) // Player
            {
                shots[i].x = (SHIP_SHOT_W/2);
                shots[i].y = y;
            }
            else // Alien
            {
                shots[i].x = (ALIEN_SHOT_W/2);
                shots[i].y = (ALIEN_SHOT_H/2);

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
        
        if(shots[i].ship) // Player
        {
            shots[i].y -= 5;

            if(shots[i].y < -SHIP_SHOT_H)
            {
                shots[i].used = false;
            }
        }
        else // Alien
        {
            shots[i].x +=  shots[i].dx;
            shots[i].y +=  shots[i].dy;

            if((shots[i].x < -ALIEN_SHOT_W) || (shots[i].x > BUFFER_W) || (shots[i].y < -ALIEN_SHOT_H) || (shots[i].y > BUFFER_H)) 
            {
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
        
        // Checa se o tiro nao eh da propria nave
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

        if(shots[i].ship) // Player
            al_draw_bitmap(sprites.ship_shot[frame_display], shots[i].x, shots[i].y, 0);
        else // Alien
        {
            ALLEGRO_COLOR tint = frame_display ? al_map_rgb_f(1, 1, 1) : al_map_rgb_f(0.5, 0.5, 0.5);
            al_draw_tinted_bitmap(sprites.alien_shot, tint, shots[i].x, shots[i].y, 0);
        }
    }
}
