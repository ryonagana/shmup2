#ifndef WINDOW_HEADER
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
void window_gracefully_quit(const char *msg);
bool window_request_gracefully_closing(void);

int window_get_width(void);
int window_get_height(void);

ALLEGRO_DISPLAY* get_window_display(void);
ALLEGRO_EVENT_QUEUE* get_window_queue(void);
ALLEGRO_TIMER *get_window_timer(void);
ALLEGRO_TIMER *get_window_actual_time(void);

int64_t get_window_time_ms(void);
void     set_window_time_ms(int64_t time);


#endif
