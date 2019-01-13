#ifndef MOUSE_HEADER
#define MOUSE_HEADER

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

typedef  struct MOUSE {
    bool lButton;
    bool rButton;
    int x;
    int y;
    double z;

}MOUSE;

void mouse_init(void);
void mouse_destroy(void);

MOUSE *mouse_get(void);
void mouse_update(ALLEGRO_EVENT *e);

#endif
