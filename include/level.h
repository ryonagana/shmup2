#ifndef LEVEL_HEADER
#define LEVEL_HEADER

#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdint>
#include <cstdbool>
#include <ostream>
#include <fstream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "shared.h"
#include "spaceship.h"

#define MAX_GRID_X 200
#define MAX_GRID_Y 100

#define MAX_ENEMIES_MAP 150
#define MAX_ITEMS_MAP   100

#define MAX_LEVEL_KEYS 4

#define TILE_SIZE 32


#define MAP_ID "CBMAP\0"
#define MAP_VER 1
typedef struct TILE {
    int32_t id;
    bool passable;
    bool block;
    int flags;
}TILE;



typedef struct MAPCOORD {
    unsigned char x,y;
}MAPCOORD;


/*
class Map {
public:
    Map();
    ~Map();

    bool Save(const std::string& filepath);
    bool Load(const std::string& filepath);
private:
    char m_magic[6];
    std::vector<TILE> m_tiles_layer;
    std::vector<TILE> m_bg_layer;
    //std::vector<TILE> obj_layer;
    std::string m_map_name;
    SPACESHIP *m_player;
    int m_width;
    int m_height;

};
*/




typedef struct LEVEL {
    char magic[6]; // CBMAP
    int  ver;
    std::string mapname;
    std::string filename;
    std::string level_path;
    MAPCOORD player_pos;
    MAPCOORD keys[MAX_LEVEL_KEYS];
    bool valid_file;
    byte map_width;
    byte map_height;
    uint16_t powerup_count;
    unsigned char background_id;
    TILE bg_layer [MAX_GRID_Y][MAX_GRID_X];
    TILE map_layer[MAX_GRID_Y][MAX_GRID_X];
    TILE obj_layer[MAX_GRID_Y][MAX_GRID_X];

    LEVEL(){
        mapname = "";
        filename = "";
    }



}LEVEL;


void level_init_default(LEVEL* level);



bool level_save(LEVEL *lvl, const std::string mapname);
bool level_load(LEVEL *lvl, const std::string mapname);

bool level_save_memory(LEVEL *lvl);
bool level_load_memory(LEVEL *lvl);

bool level_file_exists(const char *mapname);
TILE *level_get_tile(TILE map[MAX_GRID_Y][MAX_GRID_X], int x, int y);
void level_map_copy(LEVEL *dest, const LEVEL *orig);



#endif
