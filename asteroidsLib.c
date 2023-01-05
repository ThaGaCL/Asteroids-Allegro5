#include "asteroidsLib.h"


long frames;
long score;

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