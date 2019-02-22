#include "particle.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include "window.h"

void particle_create(PARTICLE *particle, VECTOR2 pos, VECTOR2 origin, float scale, float shrink_rate, float speed,  float angle, int duration, ALLEGRO_COLOR color)
{
    if(!particle){
        particle = new PARTICLE; //(PARTICLE*) malloc(sizeof(PARTICLE));
    }
    vector_Copy(&particle->position, &pos);
    vector_Copy(&particle->origin, &origin);

    particle->duration = duration;
    particle->color = color;
    particle->speed = speed;
    particle->shrink_rate = shrink_rate;

    particle->direction.x = cos(angle);
    particle->direction.y = sin(angle);
    particle->scale = scale;
    particle->is_alive = true;


}

void particle_set(PARTICLE *particle, VECTOR2 pos, VECTOR2 origin, float dir_x, float dir_y, float scale, float shrink_rate, float speed, float angle, int duration, ALLEGRO_COLOR color)
{
    vector_Copy(&particle->position, &pos);
    vector_Copy(&particle->origin, &origin);

    particle->duration = duration;
    particle->color = color;
    particle->speed = speed;
    particle->shrink_rate = shrink_rate;

    particle->direction.x = cos(angle);
    particle->direction.y = sin(angle);
    particle->scale = scale;
}

void particle_update(PARTICLE *particle)
{


    particle->position.x += particle->direction.x * particle->speed;
    particle->position.y += particle->direction.y * particle->speed;

    particle->duration -= 1;

    if(particle->position.x >= window_get_width() ){
        particle->is_alive = false;
    }

    if(particle->position.y >= window_get_height() ){
        particle->is_alive = false;
    }

    if(particle->position.x < 0 ){
        particle->is_alive = false;
    }

    if(particle->position.y < 0 ){
        particle->is_alive = false;
    }

    if(particle->duration <= 0 || particle->scale <= 0){
        particle->is_alive = false;
    }
}
void particle_draw(PARTICLE *particle, ALLEGRO_BITMAP *bmp)
{
    if(!particle->is_alive) return;
    if(!bmp){

        float x1 = particle->position.x;
        float x2 = particle->position.x + 5.0f;
        float y1 = particle->position.y;
        float y2 = particle->position.y + 5.0f;

        al_draw_filled_rectangle(x1,y1,x2,y2, particle->color);
        return;
    }


    al_draw_tinted_scaled_bitmap(bmp, particle->color, 0,0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), particle->position.x, particle->position.y,al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), 0);
}

void particle_destroy(PARTICLE *particle){
    if(particle) free(particle);
    particle = NULL;
}
