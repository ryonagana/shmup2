#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER
#include <cstdio>
#include <allegro5/allegro.h>
#include "vector2.h"


class CParticle {


public:
    float x,y;
    float dir_x, dir_y;
    int life;
    bool alive;
    ALLEGRO_COLOR color;
    ALLEGRO_BITMAP *bmp;

    CParticle();
    CParticle(float x, float y, float dir_x, float dir_y, int life, ALLEGRO_COLOR color);
    ~CParticle();
    void Set(float x, float y, float dir_x, float dir_y, int life, ALLEGRO_COLOR color);
    void Update();
    void Draw();
};


#endif
