#ifndef TILES_HEADER

#define TILES_HEADER

#include <cstdio>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include "level.h"
#include "Utils/CRect.h"


typedef enum SPECIAL_TILES_ID {
    SPECIAL_TILE_PLAYER_POS,
    SPECIAL_TILE_COUNT

}TILE_SPECIAL_PLAYER;

typedef enum TILE_ID {
    NO_TILE=99,
    TILE_GROUND01_F=0,
    TILE_GROUND01_TOP_L,
    TILE_GROUND01_TOP_R,
    TILE_GROUND02_ROCK_TOP,
    TILE_GROUND02_ROCK_F,
    TILE_COUNT


}TILE_ID;


typedef struct TILEINFO {

    TILE_ID id;
    Utils::CRect rect;
    TILEINFO(){
        id = NO_TILE;
    }

    TILEINFO(TILE_ID tid = NO_TILE, const Utils::CRect r = {0,0,0,0}){
        id = tid;
        rect = r;
    }

}TILEINFO;


#define GET_TILE(a,x)  (a[x] != NULL ? a[x] : a[NO_TILE])

bool tiles_init(void);
void tiles_destroy(void);

Utils::CRect tiles_get_by_id(unsigned char id);
void tiles_draw(const Utils::CRect r, float x, float y);
ALLEGRO_BITMAP* tiles_draw_tile_bmp(ALLEGRO_BITMAP *dst, const Utils::CRect r);
void tiles_set_properties(TILE *tile);


/*
ALLEGRO_BITMAP *tilemap_get_bmp(void);
ALLEGRO_BITMAP *tiles_get_by_id(unsigned char id);
ALLEGRO_BITMAP *special_tiles_get_by_id(unsigned char id);
void tiles_set_properties(TILE *tile);
TILEINFO *tiles_get_name(TILE_ID id);
*/
#endif
