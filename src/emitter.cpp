#include <iostream>
#include "emitter.h"
#include "shared.h"


PARTICLE_EMITTER* emitter_create(VECTOR2 pos, VECTOR2 origin,  float scale, float shrink_rate,  int duration, size_t amount, int max_speed, ALLEGRO_COLOR color)
{
     /* TODO */
    PARTICLE_EMITTER *emitter = nullptr;


    emitter = new PARTICLE_EMITTER;
    emitter->particles = new (std::nothrow) PARTICLE[amount + 1]; // (PARTICLE*)  malloc(sizeof(PARTICLE) * amount + 1);
    //memset(emitter->particles,0, sizeof(PARTICLE) * amount + 1);
    emitter->size = amount;


    emitter->position = pos;
    emitter->origin   = origin;

    emitter->scale = scale;
    emitter->shrink_rate = shrink_rate;
    emitter->duration = duration;
    emitter->max_speed = max_speed;
    emitter->color = color;

    for(unsigned int i = 0; i < amount;i++){
       int speed = rand() % max_speed + 1;
       particle_create(&emitter->particles[i], pos, origin, scale, shrink_rate, speed, duration, color);
       emitter->particles[i].is_alive = false;
    }

    return emitter;

}


void emitter_destroy(PARTICLE_EMITTER *emitter){

    delete[] emitter->particles;
    if(emitter) delete[] emitter;

    emitter->particles =  nullptr;
    emitter = nullptr;
}

void emitter_update(PARTICLE_EMITTER *emitter, int64_t time, float dir_x, float dir_y, int duration, float speed, float angle){

    for(unsigned int i = 0; i < emitter->size; i++){

        particle_update(&emitter->particles[i]);

        if(!emitter->particles[i].is_alive){

            PARTICLE *dead = emitter_find_dead_particle(emitter->particles, (int)emitter->size);
            int n_speed = RAND_INT(1, speed) + RAND_INT(1, time);
            //particle_set(dead, emitter->position, emitter->origin, dir_x, dir_y,  emitter->scale, emitter->shrink_rate, n_speed, angle, duration, emitter->color);
            dead->is_alive = true;
        }

    }
}

void emitter_draw(PARTICLE_EMITTER *emitter, ALLEGRO_BITMAP *tex){

    for(unsigned int i = 0; i < emitter->size; i++){
        if(emitter->particles[i].is_alive){
            particle_draw(&emitter->particles[i], tex);
        }
    }
}

PARTICLE *emitter_find_dead_particle(PARTICLE *particles, int max){
    int i = 0;
    while(particles[i].is_alive && i < max) i++;

    if(i == max) return nullptr;

    return &particles[i];
}

void emitter_burst(PARTICLE_EMITTER *emitter, float x, float y, int spread, int life, ALLEGRO_BITMAP *bmp){

    PARTICLE *p = nullptr;

    for(size_t i = 0; i < emitter->size; i++){
        p = emitter_find_dead_particle(emitter->particles, emitter->size);
        if(p != nullptr){
            VECTOR2 pos;
            VECTOR2 origin;

           vector_Init(&pos, x,y);
           vector_Copy(&origin, &emitter->origin);

           //particle_set(p, pos, origin, RAND_INT(0.5,100) / 100.0 * spread, RAND_INT(0.5,100) / 100.0 * spread, 1.0, 0.5f, RAND_INT(1,100), RAND_INT(0,180), life ? life : 100, al_map_rgb(255,0,0));

            //particle_set(p, pos
        }
    }
}