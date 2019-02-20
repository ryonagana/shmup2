#ifndef MOUSE_HEADER
#define MOUSE_HEADER

#include <cstdio>
#include <cstdbool>
#include <cstdlib>
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
void  mouse_set(int x, int y);
void mouse_update(ALLEGRO_EVENT *e);

#endif
