#ifndef TILES_HEADER

#define TILES_HEADER

#include <cstdio>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include "level.h"



typedef enum SPECIAL_TILES_ID {
    SPECIAL_TILE_PLAYER_POS,
    SPECIAL_TILE_COUNT

}TILE_SPECIAL_PLAYER;

typedef enum TILE_ID {
    NO_TILE=0,
    TILE_GROUND01_F,
    TILE_GROUND01_TOP_L,
    TILE_GROUND01_TOP_R,
    TILE_GROUND02_ROCK_TOP,
    TILE_GROUND02_ROCK_F,
    TILE_COUNT


}TILE_ID;


typedef struct TILEINFO {
    std::string name;
    TILE_ID id;
    TILEINFO(){
        name = "";
        id = NO_TILE;
    }

    TILEINFO(const std::string &tname , TILE_ID tid = NO_TILE){
        name = tname;
        id = tid;
    }

}TILEINFO;


#define GET_TILE(a,x)  (a[x] != NULL ? a[x] : a[NO_TILE])

bool tiles_init(void);
void tiles_destroy(void);
ALLEGRO_BITMAP *tilemap_get_bmp(void);
ALLEGRO_BITMAP *tiles_get_by_id(unsigned char id);
ALLEGRO_BITMAP *special_tiles_get_by_id(unsigned char id);
void tiles_set_properties(TILE *tile);
TILEINFO *tiles_get_name(TILE_ID id);
#endif
