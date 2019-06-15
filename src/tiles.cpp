#include "tiles.h"
#include "tiles.h"
#include "path.h"
#include "shared.h"
#include "window.h"

#include <algorithm>
#include <vector>

#define MAX_TILE_COUNT 255

static ALLEGRO_BITMAP *tileset = nullptr;
static Utils::CRect tileArray[MAX_TILE_COUNT] = {};



bool tiles_init(void){

    tileArray[NO_TILE] = {0,0,0,0};
    tileArray[TILE_GROUND01_F] = {0,0,32,32};
    tileArray[TILE_GROUND01_TOP_L] = {0,128,32,32};
    tileArray[TILE_GROUND01_TOP_R] = {0,96,32,32};
    tileArray[TILE_GROUND02_ROCK_F] = {0,25,32,32};
    tileArray[TILE_GROUND02_ROCK_TOP] = {0,25,32,32};



    char *path = get_file_path("tile", "spritesheet.png");

    tileset = al_load_bitmap(path);

    if(!tileset){
        delete path;
        return false;
    }




    return true;

}

void tiles_destroy(void){
    if(tileset) al_destroy_bitmap(tileset);
}



Utils::CRect tiles_get_by_id(unsigned char id){

    return tileArray[id];
}

/*
static ALLEGRO_BITMAP *tileset = nullptr;
static ALLEGRO_BITMAP *special_tileset = nullptr;

static ALLEGRO_BITMAP* tiles_sub_bmp[TILE_COUNT + 1];
static ALLEGRO_BITMAP* tiles_special_sub_bmp[SPECIAL_TILE_COUNT];





static void tiles_load_from_file(const char *filename);



static std::vector<TILEINFO*> tile_names;


static char* tile_names[TILE_COUNT + 1] = {
    "No Tile\0",
    "Tile Ground 01  Flat\0",
    "Tile Ground 01  Top R\0",
    "Tile Ground 01  Yop L\0",
    nullptr,
};


bool tiles_init(void){
    char *filepath = get_file_path("tile", "spritesheet.png");
    bool tileset_not_found = true;



    tile_names.push_back( new TILEINFO("No Tile", NO_TILE));
    tile_names.push_back( new TILEINFO("Tile Ground 01  Flat", TILE_GROUND01_F));
    tile_names.push_back( new TILEINFO("Tile Ground 01  TOP R", TILE_GROUND01_TOP_R));
    tile_names.push_back( new TILEINFO("Tile Ground 01  TOP L", TILE_GROUND01_TOP_L));

    if(!filepath){
       CRITICAL("%s not found!", filepath);
       return false;
    }

    tileset = al_load_bitmap(filepath);
    filepath = nullptr;
    filepath = get_file_path("tile", "special_tileset.png");

    special_tileset = al_load_bitmap(filepath);

    if(!special_tileset){
        CRITICAL(" Special tileset not found!");
    }

    tileset_not_found = (tileset == nullptr) ? true : false;


    LOG("Spritesheet: %s successfully loaded!", filepath);

    if(filepath) delete[] filepath;

    //reset list of tiles to nullptr!
    for(int i = 0; i < TILE_COUNT + 1; i++){
        tiles_sub_bmp[i] = nullptr;
    }

    for(int i = 0; i < SPECIAL_TILE_COUNT; i++){
        tiles_special_sub_bmp[i] = nullptr;
    }




    tiles_sub_bmp[NO_TILE] = al_create_bitmap(32,32);

    al_set_target_bitmap(tiles_sub_bmp[NO_TILE]);
    al_clear_to_color(al_map_rgba_f(0,255,0,1));
    al_set_target_backbuffer(get_window_display());

    if(!tileset){
        for(unsigned int i = 0; i < TILE_COUNT; i++){
            tiles_sub_bmp[i] = al_clone_bitmap( tiles_sub_bmp[NO_TILE]);
        }
    }



    //tiles_load_from_file("tiles.txt");


    tiles_sub_bmp[TILE_GROUND01_F] = al_create_sub_bitmap(tileset,0,0,32,32);
    tiles_sub_bmp[TILE_GROUND01_TOP_L] = al_create_sub_bitmap(tileset,96,0,32,32);
    tiles_sub_bmp[TILE_GROUND01_TOP_R] = al_create_sub_bitmap(tileset,128,0,32,32);
    tiles_sub_bmp[TILE_GROUND02_ROCK_F] = al_create_sub_bitmap(tileset,32,0,32,32);
    tiles_sub_bmp[TILE_GROUND02_ROCK_TOP] = al_create_sub_bitmap(tileset,64,0,32,32);

    tiles_special_sub_bmp[SPECIAL_TILE_PLAYER_POS] = al_create_sub_bitmap(special_tileset,0,0,32,32);

    return true;


}


ALLEGRO_BITMAP* tilemap_get_bmp(void){
    if(tileset == nullptr) return nullptr;
    return tileset;
}

void tiles_destroy(void){

    for(unsigned int i = 0; i < TILE_COUNT; i++){
        if(tiles_sub_bmp[i]) al_destroy_bitmap(tiles_sub_bmp[i]);
    }

    if(tileset) al_destroy_bitmap(tileset);
}


ALLEGRO_BITMAP *tiles_get_by_id(unsigned char id){
    return tiles_sub_bmp[id] != nullptr ? tiles_sub_bmp[id] : tiles_sub_bmp[NO_TILE];
}

ALLEGRO_BITMAP *special_tiles_get_by_id(unsigned char id){
    return tiles_special_sub_bmp[id] != nullptr ? tiles_special_sub_bmp[id] : tiles_sub_bmp[NO_TILE];
}



TILEINFO *tiles_get_name(TILE_ID id){

    auto it = std::find_if(tile_names.begin(), tile_names.end(), [&id](TILEINFO *info) { return info->id == id; } );
    return *it.base();

}

static void tiles_load_from_file(const char *filename){
    ALLEGRO_FILE *fp = nullptr;
    char *fullpath = nullptr;

    fullpath = get_file_path(nullptr, filename);
    LOG("LOAD TILE LIST: %s", fullpath);
    if(!al_filename_exists(fullpath)){
        al_show_native_message_box(get_window_display(), "Error:", "An Error Occured!", "Missing tiles.txt sorry", nullptr , 0);
        window_exit_loop();
        window_gracefully_quit("tiles do not exists");
        return;
    }

    fp = al_fopen(fullpath, "rb");

    if(!fp){
        al_show_native_message_box(get_window_display(), "Error:", "An Error Occured!", "Missing tiles.txt sorry", nullptr , 0);
        window_gracefully_quit("filename cant find tiles.txt");
        return;
    }

    char linefeed[127];
    char *line = nullptr;

     al_fgets(fp, linefeed, sizeof(char) * 127);

     while(al_fgets(fp,linefeed, sizeof(char) * 127) != nullptr){
        int id, offsetx, offsety, width, height;

        line = strtok(linefeed,";");
        if(*line == '\n') break;

        id = atoi(line);
        line = nullptr;

        line = strtok(nullptr, ";");
        offsetx = atoi(line);
        line = nullptr;

        line = strtok(nullptr, ";");
        offsety = atoi(line);
        line = nullptr;

        line = strtok(nullptr, ";");
        width  = atoi(line);
        line = nullptr;

        line = strtok(nullptr, ";");
        height = atoi(line);
        line = nullptr;

        memset(linefeed,0, sizeof(char) * 127);
        printf("\nID: %d X: %d Y: %d WIDTH: %d HEIGHT: %d\n\n", id, offsetx, offsety, width, height);
        tiles_sub_bmp[id] = al_create_sub_bitmap(tileset,offsetx,offsety,width,height);

     }

    al_fclose(fp);

}
*/

void tiles_draw(const Utils::CRect r, float x, float y)
{
    al_draw_bitmap_region(tileset, r.X(), r.Y(), r.W(), r.H(), x,y,0);
}

ALLEGRO_BITMAP *tiles_draw_tile_bmp(ALLEGRO_BITMAP *dst, const Utils::CRect r)
{
    if(dst == nullptr) return nullptr;

    al_set_target_bitmap(dst);
    tiles_draw(r,0,0);
    al_set_target_backbuffer(get_window_display());

    return dst;
}

void tiles_set_properties(TILE *tile){
    switch (tile->id) {
        case NO_TILE:
            tile->block = false;
            tile->passable = true;
        break;
        case TILE_GROUND01_F:
            tile->block = true;
            tile->passable = false;
        break;

        case TILE_GROUND01_TOP_L:
            tile->block = true;
            tile->passable = false;
        break;
        case TILE_GROUND01_TOP_R:
            tile->block = true;
            tile->passable = false;
        break;
    }
}

