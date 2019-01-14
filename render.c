#include "render.h"
#include "tiles.h"
#include "level.h"
#include "mouse.h"
#include "config.h"


void  render_background_color(LEVEL *level){
    ALLEGRO_COLOR col;
    switch(level->background_id){

        case 1:
            col = al_map_rgba(0,0,0,255);
        break;
        case 2:
            col = al_map_rgba(91,45,255,255);
        break;
        default:
        case 3:
            col = al_map_rgba(10,21,99,255);
        break;
    }

    al_clear_to_color(col);
}

void  render_tilemap(LEVEL *level, CAMERA *scroll){

    for(int y = 0; y < level->map_height; y++){
        for (int x = 0; x < level->map_width ; x++) {




             //background
            al_draw_bitmap( tiles_get_by_id( (int) level->map_layer[y][x].id ), (TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y,0);
           // al_draw_bitmap_region(tilemap_get_bmp(),0, 0, TILE_SIZE,TILE_SIZE, (TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y, 0 );
        }
    }


}
