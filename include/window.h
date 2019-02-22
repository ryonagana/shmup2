#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdbool>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_native_dialog.h>


void window_init(void);
void window_close(void);
bool window_open(void);
void window_exit_loop(void);
void window_gracefully_quit(const std::string &msg);
bool window_request_gracefully_closing(void);

int window_get_width(void);
int window_get_height(void);

ALLEGRO_DISPLAY* get_window_display(void);
ALLEGRO_EVENT_QUEUE* get_window_queue(void);
ALLEGRO_TIMER *get_window_timer(void);
ALLEGRO_TIMER *get_window_actual_time(void);
ALLEGRO_BITMAP *get_window_screen(void);

int64_t get_window_time_ms(void);
void     set_window_time_ms(int64_t time);

#define TICKSPERFRAME 60.0
#define WINDOW_STOP_TIMER() do { al_stop_timer(get_window_timer()); }while(0);
#define WINDOW_RESUME_TIMER() do { al_start_timer(get_window_timer());al_set_timer_speed(get_window_timer(), 1.0 / TICKSPERFRAME ); }while(0);

#endif
