#ifndef KEYBOARD_HEADER
#define KEYBOARD_HEADER
#include <stdio.h>
#include <allegro5/allegro.h>

void keyboard_start(void);
int  keyboard_pressed(int key);
void keyboard_map(ALLEGRO_EVENT *e);
#endif
