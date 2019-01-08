#include "spaceship.h"
#include "keyboard.h"
#include "window.h"


static struct SPACESHIP  player_list[MAX_SPACESHIPS]=
{
        {250,100,3,{0},0},
        {250,100,3,{0},0}
};





void spaceship_scrolling_update(SPACESHIP *spaceship, SCROLLING *scrolling){
    scrolling->x = (spaceship->x) - window_get_width() /  2;
    scrolling->y = (spaceship->y) - window_get_height() / 2;
}

void spaceship_move(int num,   float x, float y)
{
    struct SPACESHIP* player = NULL;
    player = spaceship_get_player(num);

    player->x += x * player->speed;
    player->y += y * player->speed;

}


SPACESHIP *spaceship_get_player(int num){
    if(num > MAX_SPACESHIPS) return NULL;
    return &player_list[num] != NULL ? &player_list[num] : NULL;
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
