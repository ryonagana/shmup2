#include "keyboard.h"

static int key_list[ALLEGRO_KEY_MAX];

void keyboard_start(void){
    int i;
    for(i = 0; i < ALLEGRO_KEY_MAX; i++){
        key_list[i] = 0;
    }
}



int keyboard_pressed(int key){
    return (int)key_list[key];
}

int keyboard_released(int key){
    return (int)!key_list[key];
}

void keyboard_map(ALLEGRO_EVENT *e){
    if(e->type == ALLEGRO_EVENT_KEY_UP) {
        key_list[e->keyboard.keycode] = 0;
    }

    if(e->type == ALLEGRO_EVENT_KEY_DOWN){
        key_list[e->keyboard.keycode] = 1;
    }
}
