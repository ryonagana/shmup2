#include "config.h"
#include "path.h"
#include "shared.h"
#include <string.h>
#include <math.h>
#include <stdarg.h>


static ALLEGRO_CONFIG *settings_conf = nullptr;

static SETTINGS settings;


void config_create_default(ALLEGRO_FILE *fp_cfg){


    settings.sfx_volume.f_field = 1.0;
    settings.music_volume.f_field = 1.0;
    settings.sfx_on.i_field = 1;
    settings.music_on.i_field = 1;
    settings.opengl.i_field = 1;
    settings.editor_mode.i_field = 1;
    settings.fullscreen.i_field = 0;



    al_add_config_section(settings_conf, "config");

    config_set_key(settings_conf, "sfx_volume", "%.1f", settings.sfx_volume.f_field);
    config_set_key(settings_conf, "music_volume", "%.1f", settings.music_volume.f_field);
    config_set_key(settings_conf, "sfx_on", "%d", settings.sfx_on.i_field);
    config_set_key(settings_conf, "music_on", "%d", settings.music_on.i_field);
    config_set_key(settings_conf, "opengl", "%d", settings.opengl.i_field);
    config_set_key(settings_conf, "fullscreen", "%d", settings.fullscreen.i_field);
     config_set_key(settings_conf, "editor_mode", "%d", settings.editor_mode.i_field);
    al_save_config_file_f(fp_cfg, settings_conf);
}

bool config_init(void){
    char *path = get_file_path(nullptr, "config.ini");
    ALLEGRO_FILE *fp =  nullptr;

    if(!al_filename_exists(path)){
        fp = al_fopen(path, "wb");
        settings_conf = al_create_config();
        config_create_default(fp);
        al_fclose(fp);

    }

    settings_conf = al_load_config_file(path);




    settings.sfx_volume.f_field = atof(config_get_key(settings_conf, "sfx_volume"));
    settings.music_volume.f_field = atof(config_get_key(settings_conf, "music_volume"));
    settings.sfx_on.i_field = atoi(config_get_key(settings_conf, "sfx_on"));
    settings.music_on.i_field = atoi(config_get_key(settings_conf, "music_on"));
    settings.opengl.i_field = atoi(config_get_key(settings_conf, "opengl"));
    settings.fullscreen.i_field = atoi(config_get_key(settings_conf, "fullscreen"));
    settings.editor_mode.i_field = atoi(config_get_key(settings_conf,"editor_mode"));
    if(fp) al_fclose(fp);
    if(path)delete[] path;
    return true;

}

void config_set_key(ALLEGRO_CONFIG *cfg, const char *key, const char *fmt, ...){
    char key_str[56];
    va_list lst;

    const char *nfmt = fmt;

    va_start(lst, fmt);
    vsnprintf(key_str, strlen(fmt),  nfmt , lst);
    //sprintf(key_str, "%s", key_str);
    al_set_config_value(cfg, "config", key, key_str);
    va_end(lst);
}

void config_destroy(void){
    if(settings_conf) al_destroy_config(settings_conf);
}


SETTINGS* config_get(void){
    return &settings;
}

const char *config_get_key(ALLEGRO_CONFIG *cfg, const char *key){
    return al_get_config_value(cfg, "config",key);
}
