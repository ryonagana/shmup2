#include "level.h"
#include "path.h"
#include <string.h>

void level_start(LEVEL* level){

    strncpy(level->magic, MAP_ID, 4);
    level->ver = 1;
    level->player_pos.x = 100;
    level->player_pos.y = 100;
    level->background_id = 0;

    for(unsigned int i = 0; i < 4; i++){
        level->keys[i].x = 99;
        level->keys[i].y = 99;
    }

    for(int y = 0; y < MAX_GRID_H; y++){
        for(int x = 0; x < MAX_GRID_W;x++){
            level->map[y][x].id = 0;
            level->map[y][x].block = false;
            level->map[y][x].passable = false;
        }
    }

    level->powerup_count = 0;

}

bool level_load(ALLEGRO_DISPLAY *display, LEVEL *lvl, char name){

    return false;
}


bool level_save(ALLEGRO_DISPLAY *display,LEVEL *lvl, const char *mapname){
    const char * filepath = get_file_path("map", mapname);

    ALLEGRO_FILECHOOSER *chooser_diag = al_create_native_file_dialog(filepath, "Save File..", "*.*", ALLEGRO_FILECHOOSER_SAVE);

    if(!al_show_native_file_dialog(display, chooser_diag)){
        if(chooser_diag) al_destroy_native_file_dialog(chooser_diag);
        return false;
    }

    filepath = al_get_native_file_dialog_path(chooser_diag,0);

    char file_lc[4096] =  ""; // need to fit not only the filename but full path, on windows this  can be huge, so we need to use a big buffer to store the path

    strncpy(file_lc, filepath, strlen(filepath) + 1);

    for(int i = 0; file_lc[i];i++){
        file_lc[i] = (char) tolower(file_lc[i]);
    }



    ALLEGRO_FILE *fp = NULL;
    printf("path to save :%s", file_lc);
    fp = al_fopen(file_lc,"wb");

    if(fp == NULL){
        fprintf(stderr, "level_save(): FILE: %s LINE: %d - cant load %s ", __FILE__, __LINE__, file_lc);
        if(chooser_diag) al_destroy_native_file_dialog(chooser_diag);
        return false;
    }

    al_fwrite(fp, lvl->magic, strlen(lvl->magic));
    al_fputc(fp, lvl->ver);
    al_fputc(fp, lvl->player_pos.x);
    al_fputc(fp, lvl->player_pos.y);

    for(unsigned int i = 0;i < 4; i++){
        al_fputc(fp, lvl->keys[i].x);
        al_fputc(fp, lvl->keys[i].y);
    }

    al_fputc(fp, lvl->background_id);

    for(unsigned int y = 0; y < MAX_GRID_H;y++){
        for(unsigned int x = 0; x < MAX_GRID_W;x++){
            al_fputc(fp, lvl->map[y][x].id);
            al_fputc(fp, lvl->map[y][x].block);
            al_fputc(fp, lvl->map[y][x].passable);
        }
    }

    al_fclose(fp);

    if(chooser_diag) al_destroy_native_file_dialog(chooser_diag);



    return true;
}
