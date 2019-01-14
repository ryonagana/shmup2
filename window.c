#include "window.h"
#include "keyboard.h"
#include "mixer.h"
#include "path.h"
#include "shared.h"
#include "tiles.h"
#include "config.h"
#include "mouse.h"
#include "editor.h"

static ALLEGRO_EVENT_QUEUE *g_queue = NULL;
static ALLEGRO_DISPLAY *g_display = NULL;
static ALLEGRO_KEYBOARD_STATE g_kbdstate;
static ALLEGRO_BITMAP *g_screen = NULL;
static ALLEGRO_TIMER *g_timer = NULL;
static ALLEGRO_TIMER *g_time  = NULL;




#define TICKSPERFRAME 60


static bool is_window_open = false;
static bool issue_gracefully_close = false;


static int64_t timer_milliseconds = 0;


static int init_allegro(void) {


    if (!al_init()){
        CRITICAL("Error: Cannot Initialize Allegro :-(");

        //DEBUG_PRINT("Error: Cannot Initialize Allegro :-(");
        return -1;

    }

    if(!al_install_keyboard()){
        CRITICAL("Error: Cannot Install Keyboard");
        //DEBUG_PRINT(("Cannot Install Keyboard"));
        return -1;
    }

    if(!al_install_mouse()){
        CRITICAL("Error: NO MOUSE FOR YOU");
        return -1;
    }

    if(!config_init()){
        char *root = get_file_path(NULL, "config.ini");
        ALLEGRO_FILE * fp = al_fopen(root, "w");
        config_create_default(fp);
        al_fclose(fp);
        if(root) free(root);
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

    SETTINGS *settings = config_get();

    if(settings->fullscreen.b_field && settings->opengl.b_field){
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_FULLSCREEN);
    }else if(settings->opengl.b_field){
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    }




    al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR);


    g_display =  al_create_display(800, 600);

    int w,h;
    w = al_get_display_width(g_display);
    h = al_get_display_height(g_display);



    g_screen  =  al_create_bitmap(w,h);

    al_get_keyboard_state(&g_kbdstate);
    al_set_target_bitmap(g_screen);
    al_set_target_bitmap(al_get_backbuffer(g_display));


    g_timer = al_create_timer( (double) 1.0f / TICKSPERFRAME ); // main game timer updates every 1/60 secs (0.013 ms)
    g_time = al_create_timer(0.1); // 100 ms (to convert in seconds)
    g_queue = al_create_event_queue(); //create event queue


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
    // custom inits
    init_allegro();
    keyboard_start();
    mouse_init();
    init_path();
    mixer_init(2);

    if(config_get()->editor_mode.i_field){
        editor_init();
    }




    if(!tiles_init()){
        CRITICAL("Error When tried to load spritesheet");
        is_window_open = false;

        return;
    }
    is_window_open = true;
}

void window_close(void){
    destroy_path();
    mixer_destroy();
    config_destroy();
    tiles_destroy();
    mouse_destroy();

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

void window_gracefully_quit(const char *msg){
    if(!issue_gracefully_close) issue_gracefully_close = true;
    if(is_window_open) window_exit_loop();  // finish the main loop isnt finished
    if(msg == NULL){
        LOG("---- GRACEFULLY QUITED: No Message ----\n\n");
    }

    LOG("---- GRACEFULLY QUITED: %s ----\n\n", msg);
    window_close();
}


bool window_request_gracefully_closing(void){
    return issue_gracefully_close;
}


int window_get_width(void){
    return al_get_display_width(g_display);
}
int window_get_height(void){
     return al_get_display_height(g_display);
}
