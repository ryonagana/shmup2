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
       float angle = rand() % 360 + 1;
       int speed = rand() % max_speed + 1;
       particle_create(&emitter->particles[i], pos, origin, scale, shrink_rate, speed, angle, duration, color);
       emitter->particles[i].is_alive = false;
    }

    return emitter;

}


void emitter_destroy(PARTICLE_EMITTER *emitter){

    free(emitter->particles);
    if(emitter) free(emitter);

    emitter->particles =  nullptr;
    emitter = nullptr;
}

void emitter_update(PARTICLE_EMITTER *emitter, int64_t time, float dir_x, float dir_y, int duration, float speed, float angle){

    for(unsigned int i = 0; i < emitter->size; i++){

        particle_update(&emitter->particles[i]);

        if(!emitter->particles[i].is_alive){

            PARTICLE *dead = emitter_find_dead_particle(emitter->particles, (int)emitter->size);
            int n_speed = RAND_INT(1, speed) + RAND_INT(1, time);
            particle_set(dead, emitter->position, emitter->origin, dir_x, dir_y,  emitter->scale, emitter->shrink_rate, n_speed, angle, duration, emitter->color);
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
