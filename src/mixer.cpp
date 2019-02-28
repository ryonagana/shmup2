#include "mixer.h"
#include "shared.h"

static ALLEGRO_VOICE *voice = nullptr;
static ALLEGRO_MIXER *mixer = nullptr;

void mixer_init(int samples){
    al_reserve_samples(samples);
    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

    al_attach_mixer_to_voice(mixer,voice);
}


void mixer_destroy(void){
    if(voice) al_destroy_voice(voice);
    if(mixer) al_destroy_mixer(mixer);
}

void sfx_destroy(GAME_SFX* sfx){
    if(sfx->instance != nullptr) al_detach_sample_instance(sfx->instance);
    al_destroy_sample_instance(sfx->instance);
    sfx->instance = nullptr;

    if(sfx->sample  != nullptr) al_destroy_sample(sfx->sample);
    return;


}


void mixer_load_sound(GAME_SFX* sfx, const char* sound_path){
    sfx->sample = al_load_sample(sound_path);

    if(sfx->sample == nullptr){
        WARN("mixer_load_sound(): cannot load  %s sound file...", sound_path);
        return;
    }

    sfx->instance = al_create_sample_instance(sfx->sample);
    al_attach_sample_instance_to_mixer(sfx->instance, mixer);
    return;

}

void play_sfx(GAME_SFX* sfx, float volume,  float pan, float speed, ALLEGRO_PLAYMODE mode){
    al_set_sample_instance_gain(sfx->instance, volume);
    al_set_sample_instance_pan(sfx->instance, pan);
    al_set_sample_instance_speed(sfx->instance, speed);
    al_set_sample_instance_playmode(sfx->instance, mode);
    al_play_sample_instance(sfx->instance);
}
