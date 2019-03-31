#include "level.h"
#include "shared.h"
#include <ostream>
#include <fstream>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>

/*
    this level module cant be done without help of Neil Roy's Deluxe Pacman Source code help
    made me understand how to load files properly, its easier use allegro I/O funcs than stdio!!!
    https://nitehackr.github.io/games_index.html
    Thanks for the Source!
*/





void level_init_default(LEVEL* level){

    strncpy(level->magic, MAP_ID, 6);
    level->ver = MAP_VER;
    level->player_pos.x = 100;
    level->player_pos.y = 100;
    level->map_width = 75;
    level->map_height = 22;
    level->background_id = 0;
    level->valid_file = false;


    strncpy(level->mapname, "Mapa Teste", 19);

    for(unsigned int i = 0; i < 4; i++){
        level->keys[i].x = 25;
        level->keys[i].y = 25;
    }



    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->bg_layer[y][x].id = 0;
            level->bg_layer[y][x].block = false;
            level->bg_layer[y][x].passable = true;
        }
    }

    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->map_layer[y][x].id = 0;
            level->map_layer[y][x].block = false;
            level->map_layer[y][x].passable = false;
        }
    }

    for(int y = 0; y < MAX_GRID_Y; y++){
        for(int x = 0; x < MAX_GRID_X;x++){
            level->obj_layer[y][x].id = 0;
            level->obj_layer[y][x].block = false;
            level->obj_layer[y][x].passable = true;
        }
    }

    level->powerup_count = 0;

}

bool level_load(LEVEL *lvl, const std::string map_name){


    bool valid_header = false;
    sf::FileInputStream fs;
    fs.open(map_name);


    fs.read(&lvl->magic,static_cast<sf::Int64>(sizeof (char) * strnlen(MAP_ID, 6)));

    //al_fread(fp, lvl->magic, sizeof (char) * strlen(MAP_ID));

    fs.read(&lvl->ver, sizeof(unsigned char));


    if(lvl->magic[0] == 'C' && lvl->magic[1] == 'B' && lvl->magic[2] == 'M' && lvl->magic[3] == 'A' && lvl->magic[4] == 'P'){
        valid_header = true;
    }else {
        WARN("MAP HEADER INVALID");
        return false;
    }



    if(lvl->ver > MAP_VER || lvl->ver != MAP_VER){
       WARN("%s map version incorrect ", map_name.c_str());
       return false;
    }

     fs.read(&lvl->player_pos.x, sizeof(unsigned char));
     fs.read(&lvl->player_pos.y, sizeof(unsigned char));

     for(unsigned int i = 0;i < 4; i++){
         fs.read(&lvl->keys[i].x, sizeof(unsigned char));
         fs.read(&lvl->keys[i].y, sizeof(unsigned char));
     }


     fs.read(&lvl->map_width, sizeof(unsigned char));
     fs.read(&lvl->map_height, sizeof(unsigned char));

     if(lvl->map_width > MAX_GRID_X) lvl->map_width =  MAX_GRID_X;
     if(lvl->map_height > MAX_GRID_Y) lvl->map_width =  MAX_GRID_Y;

      fs.read(&lvl->background_id, sizeof(unsigned char));

     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){

             fs.read(&lvl->bg_layer[y][x].id, sizeof(unsigned char));
             fs.read(&lvl->bg_layer[y][x].block, sizeof(unsigned char));
             fs.read(&lvl->bg_layer[y][x].passable, sizeof(unsigned char));

             //lvl->bg_layer[y][x].id = (unsigned char) al_fgetc(fp);
             //lvl->bg_layer[y][x].block = (unsigned char) al_fgetc(fp);
             //lvl->bg_layer[y][x].passable = (unsigned char) al_fgetc(fp);
         }
     }

     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){
             fs.read(&lvl->map_layer[y][x].id, sizeof(unsigned char));
             fs.read(&lvl->map_layer[y][x].block, sizeof(unsigned char));
             fs.read(&lvl->map_layer[y][x].passable, sizeof(unsigned char));
         }
     }


     for(unsigned int y = 0; y < MAX_GRID_Y;y++){
         for(unsigned int x = 0; x < MAX_GRID_X;x++){
             fs.read(&lvl->obj_layer[y][x].id, sizeof(unsigned char));
             fs.read(&lvl->obj_layer[y][x].block, sizeof(unsigned char));
             fs.read(&lvl->obj_layer[y][x].passable, sizeof(unsigned char));
         }
     }

     fs.read(&lvl->valid_file, sizeof(unsigned char));

     if(lvl->valid_file == valid_header)
     {
        LOG("MAP [ %s ] LOADED SUCCESS!", map_name.c_str());
     }

     return lvl->valid_file;

}


bool level_save(LEVEL *lvl, const std::string map_name){

    std::ofstream output_map;
    output_map.open(map_name);

    if(output_map.bad()){
        CRITICAL("Error: %s not found", map_name.c_str());
        return false;
    }

    output_map << lvl->magic;
    output_map << lvl->ver;
    output_map << lvl->player_pos.x;
    output_map << lvl->player_pos.y;

    for(int i = 0; i < 4; i++){
        output_map << lvl->keys[i].x;
        output_map << lvl->keys[i].y;
    }

    output_map << lvl->map_width;
    output_map << lvl->map_height;
    output_map << lvl->background_id;

    for(unsigned int y = 0; y < MAX_GRID_Y;y++){
        for(unsigned int x = 0; x < MAX_GRID_X;x++){
            output_map << lvl->bg_layer[y][x].id;
            output_map << lvl->bg_layer[y][x].block;
            output_map << lvl->bg_layer[y][x].passable;
        }
    }

    for(unsigned int y = 0; y < MAX_GRID_Y;y++){
        for(unsigned int x = 0; x < MAX_GRID_X;x++){
            output_map << lvl->map_layer[y][x].id;
            output_map << lvl->map_layer[y][x].block;
            output_map << lvl->map_layer[y][x].passable;
        }
    }

    for(unsigned int y = 0; y < MAX_GRID_Y;y++){
        for(unsigned int x = 0; x < MAX_GRID_X;x++){
            output_map << lvl->obj_layer[y][x].id;
            output_map << lvl->obj_layer[y][x].block;
            output_map << lvl->obj_layer[y][x].passable;
        }
    }

    lvl->valid_file = true;
    output_map.close();

    return lvl->valid_file;
}


TILE *level_get_tile(TILE map[MAX_GRID_Y][MAX_GRID_X], int x, int y){
    return &(map[y][x]);
}

bool level_file_exists(const char *mapname){
    std::ofstream check;
    check.open(mapname);
    if(check.bad()) {
        check.close();
        return false;
    }

    check.close();
    return true;

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
