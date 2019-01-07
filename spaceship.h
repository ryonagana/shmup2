#ifndef SPACESHIP_H
#include <stdio.h>
#include <allegro5/allegro.h>


#define SHIP_P1 (0)
#define SHIP_P2 (1)

#define MAX_SPACESHIPS (1) //leading zero

struct spaceship{
    float x;
    float y;
    float speed;

    union {
        uint32_t all_flags;
        struct {
            uint32_t controlled: 1;
            uint32_t invincible: 1;
            uint32_t alive: 1;
            uint32_t cheat: 1;
        };
    };
    int direction;
};


void spaceship_move(int num,   float x, float y);
struct spaceship* spaceship_get_player(int num);
void spaceship_keys_handle_up(int player_num);
void spaceship_keys_handle_down(int player_num);
void spaceship_update(int player_num);

#endif
