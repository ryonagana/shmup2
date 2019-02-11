#ifndef PARTICLE_HEADER
#define PARTICLE_HEADER
#include <stdio.h>
#include <allegro5/allegro.h>
#include "vector2.h"

typedef struct PARTICLE {

    VECTOR2  position;
    VECTOR2  direction;
    VECTOR2  origin;
    int      duration;
    float speed;
    float shrink_rate;
    float scale;
    bool     is_alive;
    ALLEGRO_COLOR color;


}PARTICLE;


void particle_create(PARTICLE *particle, VECTOR2 pos, VECTOR2 origin, float scale, float shrink_rate, float speed, float angle, int duration, ALLEGRO_COLOR color);
void particle_set(PARTICLE *particle, VECTOR2 pos, VECTOR2 origin, float dir_x, float dir_y, float scale, float shrink_rate, float speed, float angle, int duration, ALLEGRO_COLOR color);
void particle_update(PARTICLE *particle);
void particle_draw(PARTICLE *particle, ALLEGRO_BITMAP *bmp);
void particle_destroy(PARTICLE *particle);

#endif
