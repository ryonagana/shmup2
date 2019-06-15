#ifndef CONFIG_HEADER
#define CONFIG_HEADER
#include <stdio.h>
#include <allegro5/allegro.h>

typedef union SETTING_FIELD {
    int     i_field;
    float   f_field;
    unsigned char b_field;
}SETTING_FIELD;

typedef struct SETTINGS {

    SETTING_FIELD sfx_volume;
    SETTING_FIELD music_volume;
    SETTING_FIELD sfx_on;
    SETTING_FIELD music_on;
    SETTING_FIELD opengl;
    SETTING_FIELD fullscreen;
    SETTING_FIELD editor_mode;

    SETTINGS(){
        sfx_volume.f_field = 1.0;
        music_volume.f_field = 1.0;
        sfx_on.b_field = true;
        music_on.b_field = true;
        opengl.b_field = true;
        fullscreen.b_field = false;
        editor_mode.b_field = true;
    }

}SETTINGS;



bool config_init(void);
void config_destroy(void);
void config_create_default(ALLEGRO_FILE *fp_cfg);
const char *config_get_key(ALLEGRO_CONFIG *cfg, const char *key);
void config_set_key(ALLEGRO_CONFIG *cfg, const char *key, const char *fmt, ...);
SETTINGS* config_get(void);
#endif
