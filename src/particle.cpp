#include "particle.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include "window.h"
#include "shared.h"

CParticle::CParticle() : CParticle(0,0,1,1,RAND_INT(1,100) ,al_map_rgb(255,0,0)){
    this->bmp = nullptr;
    return;
}

CParticle::CParticle(float x, float y, float dir_x, float dir_y, int life, ALLEGRO_COLOR color){
    this->x = x;
    this->y = y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->life = life;
    this->color = color;
    this->bmp = nullptr;
    this->alive = false;
}

void CParticle::Set(float x, float y, float dir_x, float dir_y, int life, ALLEGRO_COLOR color){
    this->x = x;
    this->y = y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->life = life;
    this->color = color;
}


void CParticle::Update(){
    this->x += dir_x;
    this->y += dir_y;
    this->life--;

    //fprintf(stdout, "Particle %d -> X: %.2f Y: %.2f LIFE: %d\n\n",1, this->x,this->y, this->life);
}

void CParticle::Draw(){
     al_draw_filled_rectangle(x,y, x + 5, y + 5, al_map_rgb(255,0,0));
    /*
    if(bmp == nullptr){
        al_draw_filled_rectangle(x,y, x + 5, y + 5, color);
        return;
    }
    al_draw_scaled_bitmap(this->bmp,0,0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), x,y,al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), 0);
    return;
    */
}

CParticle::~CParticle(){

}

