#include "keyboard.h"

static int key_list[ALLEGRO_KEY_MAX];

void keyboard_start(void){
    int i;
    for(i = 0; i < ALLEGRO_KEY_MAX; i++){
        key_list[i] = 0;
    }
}


void keyboard_key_up(ALLEGRO_EVENT *ev){
    key_list[ev->keyboard.keycode] = 1;
}

void keyboard_key_down(ALLEGRO_EVENT *ev){
      key_list[ev->keyboard.keycode] = 0;
}


int keyboard_pressed(int key){
    return (int)key_list[key];
}
