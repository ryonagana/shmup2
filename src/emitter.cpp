#include <iostream>
#include <cmath>
#include "emitter.h"
#include "shared.h"

CParticleEmitter::CParticleEmitter(float x, float y, int amount){

    this->particles = new CParticle[amount + 1];

    for(int i = 0; i < amount + 1; i++){
        this->particles[i].alive = false;
        this->particles[i].x = x;
        this->particles[i].y = y;
        this->particles[i].dir_x = 0;
        this->particles[i].dir_y = 0;
    }

    this->count = amount + 1;

}



void CParticleEmitter::Update(float angle){
    for(int i = 0; i < count;i++){
        this->particles[i].Update();

        if(!this->particles[i].alive){
            CParticle *p = FindDeadParticle();
            float dx,dy;

            dx = std::cos(angle);
            dy = std::sin(angle);
            p->Set(p->x, p->x, dx,dy, p->life ? p->life : 70, al_map_rgb(255,0,0));
            p->alive = true;
        }

    }
}

void CParticleEmitter::Draw(){
    for(int i = 0; i < count;i++){
        if(!this->particles[i].alive) return;
        this->particles[i].Draw();
    }
}



CParticle *CParticleEmitter::FindDeadParticle(){
    int i  = 0;
    while(!this->particles[i].alive && i < this->count) i++;
    return &particles[i];
}
