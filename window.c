#include "window.h"
#include "keyboard.h"

static ALLEGRO_EVENT_QUEUE *g_queue;
static ALLEGRO_DISPLAY *g_display;
static ALLEGRO_KEYBOARD_STATE g_kbdstate;
static ALLEGRO_BITMAP *g_screen;
static ALLEGRO_TIMER *g_timer;
static ALLEGRO_TIMER *g_time;
static ALLEGRO_BITMAP *g_screen;



#define TICKSPERFRAME 60


static bool is_window_open = false;


static int64_t timer_milliseconds = 0;


static int init_allegro(void) {


    if (!al_init()){

        //DEBUG_PRINT("Error: Cannot Initialize Allegro :-(");
        return -1;

    }

    if(!al_install_keyboard()){
        //DEBUG_PRINT(("Cannot Install Keyboard"));
        return -1;
    }

    if(!al_install_mouse()){
        return -1;
    }



    //init_phyfs();


    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_install_mouse();
    al_init_acodec_addon();
    al_init_native_dialog_addon();

    /*
    if(window_conf.vsync <= 0){
        al_set_new_display_option(ALLEGRO_VSYNC,2, ALLEGRO_REQUIRE);
    }
    */

    /*
    if(window_conf.fullscreen <= 0){
        al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL_3_0 | ALLEGRO_RESIZABLE);
    }else {
        al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_OPENGL_3_0 | ALLEGRO_RESIZABLE);
    }
    */

    g_display =  al_create_display(800, 600);

    int w,h;
    w = al_get_display_width(g_display);
    h = al_get_display_height(g_display);



    g_screen  =  al_create_bitmap(w,h);

    al_get_keyboard_state(&g_kbdstate);
    al_set_target_bitmap(g_screen);
    al_set_target_bitmap(al_get_backbuffer(g_display));


    g_timer = al_create_timer( (double) 1.0f / TICKSPERFRAME );
    g_time = al_create_timer(0.1);
    g_queue = al_create_event_queue();

    al_register_event_source(g_queue, al_get_display_event_source(g_display));
    al_register_event_source(g_queue, al_get_keyboard_event_source());
    al_register_event_source(g_queue, al_get_mouse_event_source());
    al_register_event_source(g_queue, al_get_timer_event_source(g_timer));

    /* register the ingame time   when the game starts  the timing starts */
    al_register_event_source(g_queue, al_get_timer_event_source(g_time));

    al_set_window_title(g_display, "SHMUP MORE LIGHT!");
    al_start_timer(g_timer);
    al_start_timer(g_time);
    al_set_target_bitmap(al_get_backbuffer(g_display));
    return 0;
}

void window_init(void){
    init_allegro();
    keyboard_start();
    is_window_open = true;
}

void window_close(void){
    if (g_display != NULL) al_destroy_display(g_display);
    if(g_queue    != NULL) al_destroy_event_queue(g_queue);
    if(g_screen   != NULL) al_destroy_bitmap(g_screen);
    if(g_timer    != NULL) al_destroy_timer(g_timer);
    if(g_time     != NULL) al_destroy_timer(g_time);
}

ALLEGRO_DISPLAY* get_window_display(void){
    return g_display;
}
ALLEGRO_EVENT_QUEUE* get_window_queue(void){
    return g_queue;
}
ALLEGRO_TIMER *get_window_timer(void){
    return g_timer;
}
ALLEGRO_TIMER *get_window_actual_time(void){
    return g_time;
}

bool window_open(void){
    return is_window_open;
}

void window_exit_loop(void){
    is_window_open = false;
}

int64_t get_window_time_ms(void){
    return timer_milliseconds;
}

void set_window_time_ms(int64_t time){
    timer_milliseconds = time;
}
