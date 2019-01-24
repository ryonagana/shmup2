#ifndef TILES_HEADER
#define TILES_HEADER

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include "level.h"


typedef enum TILE_ID {
    NO_TILE=0,
    TILE_GROUND01_F,
    TILE_GROUND01_TOP_L,
    TILE_GROUND01_TOP_R,
    TILE_GROUND_BOTTOM_L,
    TILE_GROUND_BOTTOM_R,
    TILE_DOOR01_1_CLOSED,
    TILE_DOOR01_2_CLOSED,
    TILE_DOOR01_1_OPEN,
    TILE_DOOR01_2_OPEN,
    TILE_KEY_RED,
    TILE_COUNT


}TILE_ID;



#define GET_TILE(a,x)  (a[x] != NULL ? a[x] : a[NO_TILE])

bool tiles_init(void);
void tiles_destroy(void);
ALLEGRO_BITMAP *tilemap_get_bmp(void);
ALLEGRO_BITMAP *tiles_get_by_id(TILE_ID id);
void tiles_set_properties(TILE *tile);
char *tiles_get_name(TILE_ID id);
#endif
