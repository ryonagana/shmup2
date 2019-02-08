#include "tiles.h"
#include "tiles.h"
#include "path.h"
#include "shared.h"
#include "window.h"

static ALLEGRO_BITMAP *tileset = NULL;
static ALLEGRO_BITMAP *special_tileset = NULL;

static ALLEGRO_BITMAP* tiles_sub_bmp[TILE_COUNT + 1];
static ALLEGRO_BITMAP* tiles_special_sub_bmp[SPECIAL_TILE_COUNT];


static void tiles_load_from_file(const char *filename);

static char* tile_names[TILE_COUNT + 1] = {
    "No Tile\0",
    "Tile Ground 01  Flat\0",
    "Tile Ground 01  Top R\0",
    "Tile Ground 01  Yop L\0",
    NULL,
};


bool tiles_init(void){
    char *filepath = get_file_path("tile", "spritesheet.png");
    bool tileset_not_found = true;

    if(!filepath){
       CRITICAL("%s not found!", filepath);
       return false;
    }

    tileset = al_load_bitmap(filepath);
    filepath = NULL;
    filepath = get_file_path("tile", "special_tileset.png");

    special_tileset = al_load_bitmap(filepath);

    if(!special_tileset){
        CRITICAL(" Special tileset not found!");
    }

    tileset_not_found = (tileset == NULL) ? true : false;


    LOG("Spritesheet: %s successfully loaded!", filepath);

    if(filepath) free(filepath);

    //reset list of tiles to NULL!
    for(int i = 0; i < TILE_COUNT + 1; i++){
        tiles_sub_bmp[i] = NULL;
    }

    for(int i = 0; i < SPECIAL_TILE_COUNT; i++){
        tiles_special_sub_bmp[i] = NULL;
    }




    tiles_sub_bmp[NO_TILE] = al_create_bitmap(32,32);

    al_set_target_bitmap(tiles_sub_bmp[NO_TILE]);
    al_clear_to_color(al_map_rgb(220,0,0));
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
    if(tileset == NULL) return NULL;
    return tileset;
}

void tiles_destroy(void){

    for(unsigned int i = 0; i < TILE_COUNT; i++){
        if(tiles_sub_bmp[i]) al_destroy_bitmap(tiles_sub_bmp[i]);
    }

    if(tileset) al_destroy_bitmap(tileset);
}


ALLEGRO_BITMAP *tiles_get_by_id(unsigned char id){
    return tiles_sub_bmp[id] != NULL ? tiles_sub_bmp[id] : tiles_sub_bmp[NO_TILE];
}

ALLEGRO_BITMAP *special_tiles_get_by_id(unsigned char id){
    return tiles_special_sub_bmp[id] != NULL ? tiles_special_sub_bmp[id] : tiles_sub_bmp[NO_TILE];
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


char *tiles_get_name(unsigned char id){

    return tile_names[(int)id];

}

static void tiles_load_from_file(const char *filename){
    ALLEGRO_FILE *fp = NULL;
    char *fullpath = NULL;

    fullpath = get_file_path(NULL, filename);
    LOG("LOAD TILE LIST: %s", fullpath);
    if(!al_filename_exists(fullpath)){
        al_show_native_message_box(get_window_display(), "Error:", "An Error Occured!", "Missing tiles.txt sorry", NULL , 0);
        window_exit_loop();
        window_gracefully_quit("tiles do not exists");
        return;
    }

    fp = al_fopen(fullpath, "rb");

    if(!fp){
        al_show_native_message_box(get_window_display(), "Error:", "An Error Occured!", "Missing tiles.txt sorry", NULL , 0);
        window_gracefully_quit("filename cant find tiles.txt");
        return;
    }

    char linefeed[127];
    char *line = NULL;

     al_fgets(fp, linefeed, sizeof(char) * 127);

     while(al_fgets(fp,linefeed, sizeof(char) * 127) != 0){
        int id, offsetx, offsety, width, height;

        line = strtok(linefeed,";");
        if(*line == '\n') break;

        id = atoi(line);
        line = NULL;

        line = strtok(NULL, ";");
        offsetx = atoi(line);
        line = NULL;

        line = strtok(NULL, ";");
        offsety = atoi(line);
        line = NULL;

        line = strtok(NULL, ";");
        width  = atoi(line);
        line = NULL;

        line = strtok(NULL, ";");
        height = atoi(line);
        line = NULL;

        memset(linefeed,0, sizeof(char) * 127);
        printf("\nID: %d X: %d Y: %d WIDTH: %d HEIGHT: %d\n\n", id, offsetx, offsety, width, height);
        tiles_sub_bmp[id] = al_create_sub_bitmap(tileset,offsetx,offsety,width,height);

     }

    al_fclose(fp);

}