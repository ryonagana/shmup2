#include "keyboard.h"

static int key_list[ALLEGRO_KEY_MAX];
static int key_released[ALLEGRO_KEY_MAX];
//static int key_released[ALLEGRO_KEY_MAX];

void keyboard_start(void){

    memset(key_list,0, sizeof(key_list));
    memset(key_released,0, sizeof(key_list));
    return;
}



int keyboard_pressed(int key){
    return key_list[key];
}

int keyboard_released(int key){
    return key_released[key];
}

void keyboard_update(ALLEGRO_EVENT *e){
    if(e->type == ALLEGRO_EVENT_KEY_UP) {
        key_list[e->keyboard.keycode] = 0;
        key_released[e->keyboard.keycode] = 1;
    }

    if(e->type == ALLEGRO_EVENT_KEY_DOWN){
        key_list[e->keyboard.keycode] = 1;
        key_released[e->keyboard.keycode] = 0;
    }

    memset(key_list,0, sizeof(key_list));
    memset(key_released,0, sizeof(key_list));
}
