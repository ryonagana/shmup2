#include "spaceship.h"
#include "keyboard.h"
#include "window.h"
#include "level.h"
#include "config.h"

static struct SPACESHIP  player_list[MAX_SPACESHIPS]=
{
        {250,100,3,{0},0},
        {250,100,3,{0},0}
};





void spaceship_scrolling_update(SPACESHIP *spaceship, CAMERA *scrolling, int level_width, int level_height)
{
    scrolling->x = spaceship->x + TILE_SIZE / 2  - window_get_width() /  2;
    scrolling->y = spaceship->y  + TILE_SIZE / 2 - window_get_height() / 2;

    level_width  = level_width  * TILE_SIZE;
    level_height = level_height * TILE_SIZE;

    if(scrolling->x < 0)
    {
        scrolling->x = 0;
    }

    if(scrolling->x > level_width - scrolling->width)
    {
        scrolling->x = level_width - scrolling->width;
    }

    if(scrolling->y < 0)
    {
        scrolling->y = 0;
    }

    if( scrolling->y > (level_height - scrolling->height)){
        scrolling->y = level_height - scrolling->height;
    }


    if(spaceship->x < 0){
        spaceship->x = 0;
    }

    if(spaceship->x > level_width - TILE_SIZE){
        spaceship->x = level_width - TILE_SIZE;
    }

    if(spaceship->y < 0){
        spaceship->y = 0;
    }

    if(spaceship->y > level_height - TILE_SIZE){
        spaceship->y = level_height -  TILE_SIZE ;
    }

}

void spaceship_camera_init(CAMERA *camera, SPACESHIP* ship){
    camera->width = window_get_width();
    camera->height = window_get_height();
    camera->x = ship->x + TILE_SIZE / 2  - window_get_width() /  2;
    camera->y = ship->y  + TILE_SIZE / 2 - window_get_height() / 2;
}

void spaceship_move(int num,   float x, float y)
{
    struct SPACESHIP* player = nullptr;
    player = spaceship_get_player(num);

    player->x += x * player->speed;
    player->y += y * player->speed;


}


SPACESHIP *spaceship_get_player(int num){
    if(num > MAX_SPACESHIPS) return nullptr;
    return &player_list[num] != nullptr ? &player_list[num] : nullptr;
}


bool spaceship_map_limit(SPACESHIP *ship, CAMERA *cam, int level_w, int level_h){

    level_w *= TILE_SIZE;
    level_h *= TILE_SIZE;

    if(cam->x < 0 && ship->x < 0){
       return true;
    }

    if(cam->x > (level_w - cam->width) && ship->x > (level_w - cam->width)){
        return true;
    }

    if(cam->y < 0 && ship->y < 0){
       return true;
    }

    if(cam->y > (level_h - cam->height) && ship->y > (level_h - cam->height)){
        return true;
    }

    return false;
}


void spaceship_update(int player_num){


    if(keyboard_pressed(ALLEGRO_KEY_W)){
        spaceship_move(player_num, 0,-1);
    }

    if(keyboard_pressed(ALLEGRO_KEY_S)){
        spaceship_move(player_num,0,1);
    }

    if(keyboard_pressed(ALLEGRO_KEY_A)){
        spaceship_move(player_num,-1,0);
    }

    if(keyboard_pressed(ALLEGRO_KEY_D)){
        spaceship_move(player_num,1,0);
    }
}

void spaceship_set_default_flags(SPACESHIP *sp){

    sp->alive |= 1;
    sp->controlled |= 1;
    sp->cheat |= 0;

}
