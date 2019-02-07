#ifndef EMITTER_HEADER
#define EMITTER_HEADER
#include <stdio.h>
#include "particle.h"
#include <allegro5/allegro.h>
#include "vector2.h"

typedef struct PARTICLE_NODE {
    PARTICLE *particle;
    struct PARTICLE_LIST *next;
}PARTICLE_NODE;



typedef struct PARTICLE_EMITTER {
    PARTICLE_NODE *particle_emitter;
    int size;
}PARTICLE_EMITTER;


PARTICLE_EMITTER* emitter_create(ALLEGRO_BITMAP bmp, VECTOR2 pos, float scale, float shrink_rate,  float duration, int amount, int speed, ALLEGRO_COLOR color);
void emitter_update(PARTICLE_EMITTER *emitter);
void emitter_draw(PARTICLE_EMITTER *emitter);
void emitter_destroy(PARTICLE_EMITTER *emitter);
#endif
