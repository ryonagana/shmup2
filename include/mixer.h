#ifndef MIXER_HEADER
#define MIXER_HEADER

#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

typedef struct GAME_SFX {
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *instance;
}GAME_SFX;

void mixer_init(int samples);
void mixer_destroy(void);
void sfx_destroy(GAME_SFX* sfx);
void mixer_load_sound(GAME_SFX* sfx, const char* sound_path);
void play_sfx(GAME_SFX* sfx, float volume,  float pan, float speed, ALLEGRO_PLAYMODE mode);

#endif
