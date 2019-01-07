#ifndef KEYBOARD_HEADER
#include <stdio.h>
#include <allegro5/allegro.h>

void keyboard_start(void);
void keyboard_key_up(ALLEGRO_EVENT *ev);
void keyboard_key_down(ALLEGRO_EVENT *ev);
int  keyboard_pressed(int key);
#endif
