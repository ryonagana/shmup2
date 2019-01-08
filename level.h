#ifndef LEVEL_HEADER
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#define MAX_GRID_X 200
#define MAX_GRID_Y 80

#define MAX_ENEMIES_MAP 50
#define MAX_ITEMS_MAP 25


#define MAP_ID "CBMAP"
#define MAP_VER 1
typedef struct TILE {
    unsigned char id;
    bool passable;
    bool block;
}TILE;

typedef struct MAPCOORD {
    unsigned char x,y;
}MAPCOORD;


typedef struct LEVEL {
    char magic[6]; // CBL
    int  ver;
    MAPCOORD player_pos;
    MAPCOORD keys[4];
    uint16_t powerup_count;
    unsigned char background_id;
    TILE map[MAX_GRID_Y][MAX_GRID_X];

    //TODO ENEMIES
    //TODO ITEMS
}LEVEL;

void level_init_default(LEVEL* level);
bool level_save(ALLEGRO_DISPLAY *display,LEVEL *lvl, const char * mapname);
bool level_load(ALLEGRO_DISPLAY *display, LEVEL *lvl, char *mapname);

#endif
