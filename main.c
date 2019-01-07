#include <stdio.h>
#include "window.h"
#include "keyboard.h"
#include "spaceship.h"
#include "path.h"
#include "level.h"

static SPACESHIP *player =  NULL;

static void game_update_keyboard(ALLEGRO_EVENT *e);

int main()
{
    window_init();

    player = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(player);


    LEVEL teste;
    level_start(&teste);

    level_save(get_window_display(), &teste, "teste01.cbm");


    //level_save(get_window_display(), )


    while(window_open()){
        ALLEGRO_EVENT event;

        al_wait_for_event(get_window_queue(), &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                        window_exit_loop();
        }

       if(event.type == ALLEGRO_EVENT_TIMER){
           if(event.timer.source == get_window_timer()){
               spaceship_update(SHIP_P1);

           }

           if(event.timer.source == get_window_actual_time()){
                set_window_time_ms(event.timer.count);

           }
       }


       if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
            al_acknowledge_resize(get_window_display());
       }


        game_update_keyboard(&event);


        if(al_is_event_queue_empty(get_window_queue())){
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_filled_rectangle(player->x, player->y, 32 + player->x, 32 + player->y,al_map_rgb(255,0,255));
            al_flip_display();
        }

    }

    window_gracefully_quit("Quit END OF MAIN");
    return 0;
}

static void game_update_keyboard(ALLEGRO_EVENT *e){
    keyboard_map(e);
}
