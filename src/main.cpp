#include "main.h"
#include "mouse.h"
#include "editor.h"
#include "config.h"
#include "menu.h"
#include "dir.h"
#include "CEngine.h"


typedef enum GAMESTATE {
    GAMESTATE_MENU,
    GAMESTATE_GAME,
    GAMESTATE_SELECT_MAP,
    GAMESTATE_SELECT_MAP_EDITOR,
    GAMESTATE_EDITOR
}GAMESTATE;



static SPACESHIP *player =  nullptr;
static CAMERA p1_camera;

static ALLEGRO_BITMAP *spr_player = nullptr; //test



int main(int  argc, char **argv)
{
    srand(time(nullptr));
    window_init();
    menu_init();
    player = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(player);
    CEngine mainEngine;

    spr_player = al_create_bitmap(32,32);
    al_set_target_bitmap(spr_player);
    al_clear_to_color(al_map_rgb(255,0,255));
    al_set_target_backbuffer(get_window_display());







    spaceship_camera_init(&p1_camera, player);

    while(window_open()){
        ALLEGRO_EVENT event;

        al_wait_for_event(get_window_queue(), &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                        window_exit_loop();
        }

       if(event.type == ALLEGRO_EVENT_TIMER){
           if(event.timer.source == get_window_timer()){
               mainEngine.getState()->Update(&event);
               //manager.stateActive()->Update(&event);
           }

           if(event.timer.source == get_window_actual_time()){
                set_window_time_ms(event.timer.count);

           }
       }


       if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
            al_acknowledge_resize(get_window_display());
       }



         mainEngine.getState()->UpdateInput(&event);


        if(al_is_event_queue_empty(get_window_queue())){

            mainEngine.getState()->Draw();
            al_flip_display();
        }

    }
    window_gracefully_quit("Quit END OF MAIN");
    return 0;
}



