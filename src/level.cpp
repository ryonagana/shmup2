#include "level.h"
#include "path.h"
#include <cstring>


/*
    this level module cant be done without help of Neil Roy's Deluxe Pacman Source code help
    made me understand how to load files properly, its easier use allegro I/O funcs than stdio!!!
    https://nitehackr.github.io/games_index.html
    Thanks for the Source!
*/

static void level_write_tiles_to_file(std::ofstream &fs, TILE map[MAX_GRID_Y][MAX_GRID_X], int width, int height);
static void level_read_tiles_from_file(std::ifstream &fs, TILE map[MAX_GRID_Y][MAX_GRID_X]);
static bool level_header_is_valid(char magic[6]);


void level_init_default(LEVEL* level){

    strncpy(level->magic, MAP_ID, 6);
    level->ver = MAP_VER;
    level->player_pos.x = 100;
    level->player_pos.y = 100;
    level->map_width = 75;
    level->map_height = 22;
    level->background_id = 0;
    level->valid_file = false;


    level->mapname = "Default level";

    for(unsigned int i = 0; i < 4; i++){
        level->keys[i].x = 25;
        level->keys[i].y = 25;
    }



    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->bg_layer[y][x].id = 99;
            level->bg_layer[y][x].block = false;
            level->bg_layer[y][x].passable = true;
        }
    }

    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->map_layer[y][x].id = 99;
            level->map_layer[y][x].block = false;
            level->map_layer[y][x].passable = false;
        }
    }

    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->obj_layer[y][x].id = 99;
            level->obj_layer[y][x].block = false;
            level->obj_layer[y][x].passable = true;
        }
    }

    level->powerup_count = 0;

}

bool level_load(LEVEL *lvl, const std::string mapname){
    const char *map_path_ptr = nullptr;
    bool valid = false;
    char map_path[4096] = {};
    map_path_ptr = get_file_path("map", mapname.c_str());
    strncpy(map_path, map_path_ptr, strlen(map_path_ptr) + 1);
    std::ifstream in(map_path, std::ios::binary);
    delete  map_path_ptr;
    map_path_ptr = nullptr;

    if(in.bad()){
        WARN("File not Found in %s", map_path);
        return false;
    }

    in.read(lvl->magic, sizeof(char) * 5);

    if(!level_header_is_valid(lvl->magic)){
        WARN("Wrong File: %s", map_path);
        return valid;
    }

    valid = true;
    lvl->ver = in.get();


    if( lvl->ver < MAP_VER ||  lvl->ver != MAP_VER){
        WARN("Wrong File Version, its not fatal but can cause problems!");
    }

    lvl->player_pos.x =  static_cast<byte>(in.get());
    lvl->player_pos.y =  static_cast<byte>(in.get());

    for(unsigned int i = 0;i < 4; i++){
       lvl->keys[i].x =  static_cast<byte>(in.get());
       lvl->keys[i].y =  static_cast<byte>(in.get());
    }


     lvl->map_width   =  static_cast<byte>(in.get());
     lvl->map_height  =  static_cast<byte>(in.get());
     lvl->background_id =  static_cast<byte>(in.get());


     level_read_tiles_from_file(in, lvl->bg_layer);
     level_read_tiles_from_file(in, lvl->map_layer);
     level_read_tiles_from_file(in, lvl->obj_layer);

     lvl->mapname = map_path;
     lvl->filename = mapname;
     lvl->level_path = lvl->mapname;
     lvl->valid_file = valid && lvl->ver;
     in.close();
     return lvl->valid_file;
}


bool level_save(LEVEL *lvl, const std::string mapname){

    std::ofstream out;
    const char *map_path_ptr = nullptr;
    char map_path[4096] = {};
    map_path_ptr = get_file_path("map", mapname.c_str());

    strncpy(map_path, map_path_ptr, strlen(map_path_ptr) + 1);
    delete map_path_ptr;

    out.open(map_path, std::ofstream::binary);



    out.write(lvl->magic, sizeof(char) * strlen(MAP_ID));
    out.put( static_cast<char>(lvl->ver));

    out.put(static_cast<char>(lvl->player_pos.x));
    out.put(static_cast<char>(lvl->player_pos.y));


    for(unsigned int i = 0;i < 4; i++){

       out.put( static_cast<char>(lvl->keys[i].x));
       out.put( static_cast<char>(lvl->keys[i].y));
    }

    out.put( static_cast<char>(lvl->map_width));
    out.put( static_cast<char>(lvl->map_height));
    out.put( static_cast<char>(lvl->background_id));

    level_write_tiles_to_file(out, lvl->bg_layer, lvl->map_width, lvl->map_height);
    level_write_tiles_to_file(out, lvl->map_layer, lvl->map_width, lvl->map_height);
    level_write_tiles_to_file(out, lvl->obj_layer, lvl->map_width, lvl->map_height);
    out.close();

    return true;
}


TILE *level_get_tile(TILE map[MAX_GRID_Y][MAX_GRID_X], int x, int y){
    return &(map[y][x]);
}

bool level_file_exists(const char *mapname){
    char *path = get_file_path("map", mapname);

    if(al_filename_exists(path)) return true;

    return false;
}

// copy level;
void level_map_copy(LEVEL *dest, const LEVEL *orig){

    dest->background_id = orig->background_id;

    for(int i = 0; i < 4; i++){
        dest->keys[i].x = orig[i].keys->x;
        dest->keys[i].y = orig[i].keys->y;
    }

    dest->level_path = orig->level_path;
    strncpy(dest->magic, orig->magic, 6);
    dest->map_width = orig->map_width;
    dest->map_height = orig->map_height;
    dest->player_pos = orig->player_pos;
    dest->powerup_count = orig->powerup_count;

    for(unsigned int y = 0; y < MAX_GRID_Y;y++){
        for(unsigned int x = 0; x < MAX_GRID_X;x++){
            dest->bg_layer[y][x].id = orig->bg_layer[y][x].id;
            dest->bg_layer[y][x].block = orig->bg_layer[y][x].block;
            dest->bg_layer[y][x].passable = orig->bg_layer[y][x].passable;
        }
    }

    for(unsigned int y = 0; y < MAX_GRID_Y;y++){
        for(unsigned int x = 0; x < MAX_GRID_X;x++){
            dest->map_layer[y][x].id = orig->map_layer[y][x].id;
            dest->map_layer[y][x].block = orig->map_layer[y][x].block;
            dest->map_layer[y][x].passable = orig->map_layer[y][x].passable;
        }
    }


    for(unsigned int y = 0; y < MAX_GRID_Y;y++){
        for(unsigned int x = 0; x < MAX_GRID_X;x++){
            dest->obj_layer[y][x].id = orig->obj_layer[y][x].id;
            dest->obj_layer[y][x].block = orig->obj_layer[y][x].block;
            dest->obj_layer[y][x].passable = orig->obj_layer[y][x].passable;
        }
    }

    return;
}


static void level_write_tiles_to_file(std::ofstream &fs, TILE map[MAX_GRID_Y][MAX_GRID_X], int width, int height){


    for(int y = 0; y < MAX_GRID_Y;y++){
        for(int x = 0; x < MAX_GRID_X;x++){
           fs.put(static_cast<char>(map[y][x].id));
           fs.put(static_cast<char>(map[y][x].block));
           fs.put(static_cast<char>(map[y][x].passable));
        }
    }


}

static void level_read_tiles_from_file(std::ifstream &fs, TILE map[MAX_GRID_Y][MAX_GRID_X]){
    for(int y = 0; y < MAX_GRID_Y;y++){
        for(int x = 0; x < MAX_GRID_X;x++){
           map[y][x].id = static_cast<byte>(fs.get());
           map[y][x].block = static_cast<byte>(fs.get());
           map[y][x].passable = static_cast<byte>(fs.get());
        }
    }
}



static bool level_header_is_valid(char magic[6]){
    if(magic[0] == 'C' && magic[1] == 'B' && magic[2] == 'M' && magic[3] == 'A' && magic[4] == 'P'){
       return true;
    }

    return false;
}
