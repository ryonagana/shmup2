#include "tiles.h"
#include "path.h"
#include "shared.h"
#include "window.h"
static ALLEGRO_BITMAP *tileset = NULL;


static ALLEGRO_BITMAP* tiles_sub_bmp[TILE_COUNT + 1];


bool tiles_init(void){
    char *filepath = get_file_path("tile", "spritesheet.png");
    bool tileset_not_found = true;

    if(!filepath){
       CRITICAL("%s not found!", filepath);
       return false;
    }

    tileset = al_load_bitmap(filepath);

    tileset_not_found = (tileset == NULL) ? true : false;


    LOG("Spritesheet: %s successfully loaded!", filepath);

    if(filepath) free(filepath);



    tiles_sub_bmp[NO_TILE] = al_create_bitmap(32,32);
    al_set_target_bitmap(tiles_sub_bmp[NO_TILE]);
    al_clear_to_color(al_map_rgb(220,220,220));
    al_set_target_backbuffer(get_window_display());

    if(tileset_not_found){
        tiles_sub_bmp[TILE_GROUND01_F]     =  al_clone_bitmap(tiles_sub_bmp[NO_TILE]);
        tiles_sub_bmp[TILE_GROUND01_TOP_L] =  al_clone_bitmap(tiles_sub_bmp[NO_TILE]);
        tiles_sub_bmp[TILE_GROUND01_TOP_R] =  al_clone_bitmap(tiles_sub_bmp[NO_TILE]);
        return true;
    }

    tiles_sub_bmp[TILE_GROUND01_F] = al_create_sub_bitmap(tileset,0,0,32,32);
    tiles_sub_bmp[TILE_GROUND01_TOP_L] = al_create_sub_bitmap(tileset,32,0,32,32);
    tiles_sub_bmp[TILE_GROUND01_TOP_R] = al_create_sub_bitmap(tileset,0,32,32,32);

    return true;


}


ALLEGRO_BITMAP* tilemap_get_bmp(void){
    if(tileset == NULL) return NULL;
    return tileset;
}

void tiles_destroy(void){

    for(unsigned int i = 0; i < TILE_COUNT; i++){
        if(tiles_sub_bmp[i]) al_destroy_bitmap(tiles_sub_bmp[i]);
    }

    if(tileset) al_destroy_bitmap(tileset);
}


ALLEGRO_BITMAP *tiles_get_by_id(TILE_ID id){

    ALLEGRO_BITMAP *tile = NULL;

    switch(id){
        default:
        case NO_TILE:
            tile = GET_TILE(tiles_sub_bmp, NO_TILE);
        break;
        case TILE_GROUND01_F:
            tile = GET_TILE(tiles_sub_bmp, TILE_GROUND01_F);
        break;
        case TILE_GROUND01_TOP_L:
            tile = GET_TILE(tiles_sub_bmp, TILE_GROUND01_TOP_L);
        break;
        case TILE_GROUND01_TOP_R:
            tile =  GET_TILE(tiles_sub_bmp, TILE_GROUND01_TOP_L);
        break;
    }

    return tile;
}
