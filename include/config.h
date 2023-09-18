#ifndef CONFIG_HEADER
#define CONFIG_HEADER
#include <cstdio>
#include <cstdlib>
#include <string>
#include <allegro5/allegro.h>

typedef union u_setting_field {
    int     i_field;
    float   f_field;
    unsigned char b_field;
}u_setting_field;

typedef struct settings_t {

    u_setting_field sfx_volume;
    u_setting_field music_volume;
    u_setting_field sfx_on;
    u_setting_field music_on;
    u_setting_field opengl;
    u_setting_field fullscreen;
    u_setting_field editor_mode;

    settings_t(){
        sfx_volume.f_field = 1.0;
        music_volume.f_field = 1.0;
        sfx_on.b_field = true;
        music_on.b_field = true;
        opengl.b_field = true;
        fullscreen.b_field = false;
        editor_mode.b_field = true;
    }

}settings_t;


class Config {
public:
    Config();
    bool readFromFile(const std::string& filepath);
    void Destroy();

    template<typename  T>
    static T readValue(Config& cfg, const std::string& section, const std::string &key);


    static void setIntValue(Config& cfg, const std::string& section, const std::string &key, int value);
    static void setFloatValue(Config& cfg, const std::string& section, const std::string &key, float value);
    static void setCharValue(Config& cfg, const std::string& section, const std::string &key, const char *value);

    ALLEGRO_CONFIG* getConfig() { return m_alllegro_settings; }
    //static float readInt(const Config& cfg, std::string section, std::string key);

private:
     ALLEGRO_CONFIG* m_alllegro_settings;
     bool loaded;


};



bool config_init(void);
void config_destroy(void);
void config_create_default(ALLEGRO_FILE *fp_cfg);
const char *config_get_key(ALLEGRO_CONFIG *cfg, const char *key);
void config_set_key(ALLEGRO_CONFIG *cfg, const char *key, const char *fmt, ...);
settings_t* config_get(void);
#endif
