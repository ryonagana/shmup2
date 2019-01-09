#include "render.h"
#include "tiles.h"

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

            al_draw_rectangle((32 * x) - scroll->x, (32 * y) - scroll->y, 32 - scroll->x, 32 - scroll->y, al_map_rgba(0,0,255,127), 1.0);

            //background

            al_draw_bitmap_region(tilemap_get_bmp(),0, 0, 32,32, (32 * x) - scroll->x, (32 * y) - scroll->y, 0 );
        }
    }

}
