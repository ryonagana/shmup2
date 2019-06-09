#include "render.h"
#include "tiles.h"
#include "level.h"
#include "mouse.h"
#include "config.h"

#define RENDER_MAX_LAYERS 4

#define BG_RENDER_LAYER   0
#define MAP_RENDER_LAYER  1
#define OBJ_RENDER_LAYER  2

static ALLEGRO_BITMAP *render_layer[RENDER_MAX_LAYERS] = {nullptr,nullptr,nullptr,nullptr};


void render_start(LEVEL *level){
    if(level == nullptr) return;
    for(int i = 0; i < RENDER_MAX_LAYERS ; i++){
        render_layer[i] = al_create_bitmap(TILE_SIZE * level->map_width, TILE_SIZE * level->map_height);
    }
}

void  render_destroy(){
    for(int i = 0; i < 3 ; i++){
        if(render_layer[i]) al_destroy_bitmap(render_layer[i]);
    }
}

void  render_background_color(LEVEL *level){
    ALLEGRO_COLOR col;

        switch(level->background_id){

            case 1:
                col = al_map_rgba(52, 152, 219,255);
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
    return;
}

void  render_tilemap(LEVEL *level, CAMERA *scroll, SPACESHIP *ship){



    al_set_target_bitmap(render_layer[MAP_RENDER_LAYER]);
    al_hold_bitmap_drawing(true);

    for(int y = 0; y < level->map_height; y++){
        for (int x = 0; x < level->map_width ; x++) {

             //background
            //al_draw_bitmap(tiles_get_by_id( static_cast<int>( level->bg_layer[y][x].id)), (TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y, 0 );

            // the map tiles
            if(level->map_layer[y][x].id == NO_TILE ) continue;

            Utils::CRect r = tiles_get_by_id(level->map_layer[y][x].id);
            tiles_draw(r, (TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y);

            //al_draw_bitmap( tiles_get_by_id( static_cast<int>(level->map_layer[y][x].id) ), (TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y,0);

            //draw the ship
            //spaceship_draw(ship, scroll);

            //draw the highest layer for givbe the illusion the player is behind a wall or something
            //al_draw_bitmap( tiles_get_by_id( static_cast<int>(level->obj_layer[y][x].id) ), (TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y,0);

        }
    }
    al_hold_bitmap_drawing(false);
    al_set_target_backbuffer(get_window_display());

    al_set_target_bitmap(render_layer[OBJ_RENDER_LAYER]);
    al_hold_bitmap_drawing(true);

    for(int y = 0; y < level->map_height; y++){
        for (int x = 0; x < level->map_width ; x++) {
            //draw the highest layer for givbe the illusion the player is behind a wall or something
            if(level->obj_layer[y][x].id != NO_TILE ){


                Utils::CRect r  = tiles_get_by_id( static_cast<int>(level->map_layer[y][x].id));


                tiles_draw(r,(TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y);

                //al_draw_bitmap( tiles_get_by_id( static_cast<int>(level->obj_layer[y][x].id) ), (TILE_SIZE * x) - scroll->x, (TILE_SIZE * y) - scroll->y,0);
            }
        }
    }
    al_hold_bitmap_drawing(false);
    al_set_target_backbuffer(get_window_display());


    al_draw_bitmap(render_layer[MAP_RENDER_LAYER],0,0,0);
    spaceship_draw(ship, scroll);
    //al_draw_bitmap(render_layer[OBJ_RENDER_LAYER],0,0,0);
}
