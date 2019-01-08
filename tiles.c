#include "tiles.h"
#include "path.h"
#include "shared.h"

static ALLEGRO_BITMAP *tileset = NULL;

bool tiles_init(void){
    const char *filepath = get_file_path("tile", "spritesheet.png");

    if(!filepath){
       CRITICAL("%s not found!", filepath);
       return false;
    }

    tileset = al_load_bitmap(filepath);

    LOG("Spritesheet: %s successfully loaded!", filepath);

    return true;

}


ALLEGRO_BITMAP* tilemap_get_bmp(void){
    if(tileset == NULL) return NULL;
    return tileset;
}
