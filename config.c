#include "config.h"
#include "path.h"
#include "shared.h"
#include <string.h>
#include <math.h>
#include <stdarg.h>

static ALLEGRO_CONFIG *settings_conf = NULL;

static SETTINGS settings;


void config_create_default(ALLEGRO_FILE *fp_cfg){


    settings.sfx_volume.f_field = 1.0;
    settings.music_volume.f_field = 1.0;
    settings.sfx_on.i_field = 1;
    settings.music_on.i_field = 1;
    settings.opengl.i_field = 1;



    al_add_config_section(settings_conf, "config");

    config_set_key(settings_conf, "sfx_volume", "%.1f", settings.sfx_volume.f_field);
    config_set_key(settings_conf, "music_volume", "%.1f", settings.music_volume.f_field);
    config_set_key(settings_conf, "sfx_on", "%d", settings.sfx_on.i_field);
    config_set_key(settings_conf, "music_on", "%d", settings.music_on.i_field);
    config_set_key(settings_conf, "opengl", "%d", settings.opengl.i_field);
    al_save_config_file_f(fp_cfg, settings_conf);
}

bool config_init(void){
    const char *path = get_file_path(NULL, "config.ini");
    ALLEGRO_FILE *fp =  NULL;

    if(!al_filename_exists(path)){
        fp = al_fopen(path, "wb");
        settings_conf = al_create_config();
        config_create_default(fp);
        al_fclose(fp);

    }

    settings_conf = al_load_config_file(path);
    if(fp) al_fclose(fp);

    return true;

}

void config_set_key(ALLEGRO_CONFIG *cfg, const char *key, const char *fmt, ...){
    char key_str[56];
    va_list lst;

    va_start(lst, fmt);
    vsnprintf(key_str, strlen(fmt), fmt, lst);
    sprintf(key_str, "%s", key_str);
    al_set_config_value(cfg, "config", key, key_str);
    va_end(lst);
}

void config_destroy(void){
    if(settings_conf) al_destroy_config(settings_conf);
}
