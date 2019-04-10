#include "tiles.h"
#include "shared.h"
#include <algorithm>
#include <vector>

/*
static ALLEGRO_BITMAP *tileset = nullptr;
static ALLEGRO_BITMAP *special_tileset = nullptr;

static ALLEGRO_BITMAP* tiles_sub_bmp[TILE_COUNT + 1];
static ALLEGRO_BITMAP* tiles_special_sub_bmp[SPECIAL_TILE_COUNT];
*/


static sf::Texture *tileset = nullptr; //we need to keed this pointer active until close
static sf::Sprite *tile_sub_bmp[TILE_COUNT + 1] = {};


static void tiles_load_from_file(const char *filename);



static std::vector<TILEINFO*> tile_names;

/*
static char* tile_names[TILE_COUNT + 1] = {
    "No Tile\0",
    "Tile Ground 01  Flat\0",
    "Tile Ground 01  Top R\0",
    "Tile Ground 01  Yop L\0",
    nullptr,
};
*/

bool tiles_init(void){
    tileset = new sf::Texture();
    tileset->loadFromFile("tile/spritesheet.png");

    sf::Image img;


    tile_names.push_back( new TILEINFO(sf::Vector2i(0,0), "No Tile", NO_TILE ));
     tile_names.push_back( new TILEINFO(sf::Vector2i(32,0), "Ground 01 Flat", TILE_GROUND01_F));
    tile_names.push_back( new TILEINFO(sf::Vector2i(96,0), "Ground 01 R", TILE_GROUND01_TOP_R));
    tile_names.push_back( new TILEINFO(sf::Vector2i(128,0), "Ground 01 L", TILE_GROUND01_TOP_L));

    for (int i = 0; i < TILE_COUNT; i++) {

    }

    for(int i = 0; i < tile_names.size(); i++){
        sf::Sprite *spr = new sf::Sprite(*tileset,sf::IntRect(tile_names[i]->pos, sf::Vector2i(32,32)));
        tile_sub_bmp[i] = spr;
    }

    return true;


}


sf::Sprite tilemap_get_bmp(void){
   sf::Sprite spr;
   spr.setTexture(*tileset);
   return spr;
}

void tiles_destroy(void){

    /*
    for(unsigned int i = 0; i < TILE_COUNT; i++){
        if(tiles_sub_bmp[i]) al_destroy_bitmap(tiles_sub_bmp[i]);
    }

    if(tileset) al_destroy_bitmap(tileset);
    */
}



sf::Sprite* tiles_get_by_id(unsigned char id){
  return tile_sub_bmp[id];
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


TILEINFO *tiles_get_name(TILE_ID id){

    auto it = std::find_if(tile_names.begin(), tile_names.end(), [&id](TILEINFO *info) { return info->id == id; } );
    return *it.base();

}

