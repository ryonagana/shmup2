#include "spaceship.h"
#include "keyboard.h"


static struct spaceship  player_list[2]=
{
        {250,100,2,{0},0},
        {0,0,2,{0},0}
};


struct spaceship_key {
    int up;
    int down;
    int left;
    int right;
    int button;
    int nobutton;
};

static struct spaceship_key spaceship_keylist[2] = {
        {0,0,0,0,0,1},
        {0,0,0,0,0,1}
};


void spaceship_move(int num,   float x, float y)
{
    struct spaceship* player = NULL;
    player = spaceship_get_player(num);

    player->x += x * player->speed;
    player->y += y * player->speed;

    printf("X: %.2f Y: %.2f\n", player->x, player->y);
}


struct spaceship* spaceship_get_player(int num){
    if(num > MAX_SPACESHIPS) return NULL;
    return &player_list[num];
}

void spaceship_keys_handle_down(int player_num){

    if(keyboard_pressed(ALLEGRO_KEY_A)){
         spaceship_keylist[player_num].left =  1;
    }

    if(keyboard_pressed(ALLEGRO_KEY_D)){
        spaceship_keylist[player_num].right =  1;
    }

    if(keyboard_pressed(ALLEGRO_KEY_W)){
        spaceship_keylist[player_num].up =  1;
    }

    if(keyboard_pressed(ALLEGRO_KEY_S)){
        spaceship_keylist[player_num].down =  1;
    }
}

void spaceship_keys_handle_up(int player_num){

    if(keyboard_pressed(ALLEGRO_KEY_A)){
         spaceship_keylist[player_num].left =  0;
    }

    if(keyboard_pressed(ALLEGRO_KEY_D)){
        spaceship_keylist[player_num].right =  0;
    }

    if(keyboard_pressed(ALLEGRO_KEY_W)){
        spaceship_keylist[player_num].up =  0;
    }

    if(keyboard_pressed(ALLEGRO_KEY_S)){
        spaceship_keylist[player_num].down =  0;
    }
}

void spaceship_update(int player_num){

    if(spaceship_keylist[player_num].up){
        spaceship_move(player_num, 0,1);
    }
    if(spaceship_keylist[player_num].down){
        spaceship_move(player_num,0,-1);
    }

    if(spaceship_keylist[player_num].left){
        spaceship_move(player_num,1,0);
    }

    if(spaceship_keylist[player_num].right){
        spaceship_move(player_num,-1,0);
    }
}
