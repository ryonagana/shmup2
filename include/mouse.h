#ifndef MOUSE_HEADER
#define MOUSE_HEADER

#include <cstdio>
#include <cstdbool>
#include <cstdlib>
#include <allegro5/allegro.h>

typedef  struct mouse_t {
    bool lButton;
    bool rButton;
    int x;
    int y;
    float z;


    mouse_t(){
        lButton = false;
        rButton = false;
        x = 0;
        y = 0;
    }



}mouse_t;

void mouse_init(void);
void mouse_destroy(void);

mouse_t *mouse_get(void);
void  mouse_set(int x, int y);
void mouse_update(ALLEGRO_EVENT *e);

#endif
