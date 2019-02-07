#include "particle.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>

void particle_create(PARTICLE *particle, VECTOR2 pos, VECTOR2 origin, float scale, float speed,  float angle, int duration, ALLEGRO_COLOR color)
{
    vector_Copy(&particle->position, &pos);
    vector_Copy(&particle->origin, &origin);

    particle->duration = duration;
    particle->color = color;
    particle->speed = speed;

    particle->direction.x = cos(angle);
    particle->direction.y = sin(angle);
    particle->scale = scale;


}
void particle_update(PARTICLE *particle)
{


    particle->position.x += particle->direction.x * particle->speed;
    particle->position.y += particle->direction.y * particle->speed;

    particle->duration -= 1;

    if(particle->duration <= 0 || particle->scale <= 0){
        particle->is_alive = false;
        particle->position.x = -100;
        particle->position.y = -100;
    }
}
void particle_draw(PARTICLE *particle, ALLEGRO_BITMAP *bmp)
{
   al_draw_tinted_scaled_bitmap(bmp, particle->color, 0,0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), particle->position.x, particle->position.y,al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), 0);
}

void particle_destroy(PARTICLE *particle){
    if(particle) free(particle);
    particle = NULL;
}
