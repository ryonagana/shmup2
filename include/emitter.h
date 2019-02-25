#ifndef EMITTER_HEADER
#define EMITTER_HEADER
#include <cstdio>
#include "particle.h"
#include <allegro5/allegro.h>
#include "vector2.h"
#include <vector>


class CParticleEmitter {
private:
    float x,y;
    CParticle *particles;
    int count;
    ALLEGRO_BITMAP *emitter_bmp;
public:
    CParticleEmitter(float x, float y, int amount);
    void Update(float angle);
    void Draw();
    CParticle* FindDeadParticle();
};




#endif
