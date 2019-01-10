#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>


#define MAX_GRID_X 200
#define MAX_GRID_Y 80

#define MAX_ENEMIES_MAP 50
#define MAX_ITEMS_MAP 25

#define TILE_SIZE 32
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
    char mapname[20];
    MAPCOORD player_pos;
    MAPCOORD keys[4];
    bool valid_file;
    unsigned char map_width;
    unsigned char map_height;
    uint16_t powerup_count;
    unsigned char background_id;
    TILE bg_layer [MAX_GRID_Y][MAX_GRID_X];
    TILE map_layer[MAX_GRID_Y][MAX_GRID_X];
    TILE obj_layer[MAX_GRID_Y][MAX_GRID_X];

    //TODO ENEMIES
    //TODO ITEMS
}LEVEL;


#endif // LEVEL_H
