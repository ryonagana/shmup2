#ifndef KEYBOARD_HEADER
#define KEYBOARD_HEADER
#include <cstdio>
#include <allegro5/allegro.h>

void keyboard_start(void);
int  keyboard_pressed(int key);
int keyboard_released(int key);
void keyboard_map(ALLEGRO_EVENT *e);
#endif
