#ifndef SPACESHIP_HEADER
#define SPACESHIP_HEADER
#include <stdio.h>
#include <allegro5/allegro.h>


#define SHIP_P1 (0)
#define SHIP_P2 (1)

#define MAX_SPACESHIPS (2) //leading zero

typedef struct SPACESHIP{
    float x;
    float y;
    float speed;

    union {
        uint32_t all_flags;
        struct {
            uint32_t controlled: 1;
            uint32_t god_mode: 1;
            uint32_t alive: 1;
            uint32_t cheat: 1;
        };
    };
    int direction;
} SPACESHIP;

typedef struct CAMERA {
    float x,y;
    int width,height;
}CAMERA;



void spaceship_move(int num,   float x, float y);
SPACESHIP* spaceship_get_player(int num);
void spaceship_update(int player_num);
bool spaceship_map_limit(SPACESHIP *ship, CAMERA *cam, int level_w, int level_h);
void spaceship_set_default_flags(SPACESHIP *sp);


void spaceship_camera_init(CAMERA *camera, SPACESHIP* ship);
void spaceship_scrolling_update(SPACESHIP *spaceship, CAMERA *scrolling, int level_width, int level_height);

#endif
