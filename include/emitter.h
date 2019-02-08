#ifndef EMITTER_HEADER
#define EMITTER_HEADER
#include <stdio.h>
#include "particle.h"
#include <allegro5/allegro.h>
#include "vector2.h"





typedef struct PARTICLE_EMITTER {
    PARTICLE *particles;
    size_t size;
    VECTOR2 position;
    VECTOR2 origin;
    float scale;
    float shrink_rate;
    int duration;
    int max_speed;
    ALLEGRO_COLOR color;
}PARTICLE_EMITTER;


PARTICLE_EMITTER* emitter_create(VECTOR2 pos, VECTOR2 origin,  float scale, float shrink_rate,  int duration, size_t amount, int max_speed, ALLEGRO_COLOR color);
void emitter_destroy(PARTICLE_EMITTER *emitter);


void emitter_clear(PARTICLE_EMITTER *emitter);
void emitter_update(PARTICLE_EMITTER *emitter);
void emitter_draw(PARTICLE_EMITTER *emitter, ALLEGRO_BITMAP *tex);

#endif
