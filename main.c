#include <stdio.h>
#include "window.h"
#include "keyboard.h"
#include "spaceship.h"
#include "path.h"
#include "level.h"
#include "shared.h"

static SPACESHIP *player =  NULL;
static SCROLLING p1_scroll;

static void game_update_keyboard(ALLEGRO_EVENT *e);

int main()
{
    window_init();

    player = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(player);



    LEVEL teste;
    level_start(&teste);
    //level_save(get_window_display(), &teste, "level01");


    if(!level_load(get_window_display(), &teste, "level01")){
        CRITICAL("level not loaded correctly, sorry");
    }


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
               spaceship_scrolling_update(player, &p1_scroll);

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


            //render map?
            for(int y = 0; y < MAX_GRID_Y; y++){
                for (int x = 0; x < MAX_GRID_X ; x++) {
                    al_draw_rectangle(32 * x, 32 * y, 32, 32, al_map_rgba(0,0,255,255), 1.0);

                    //al_draw_line(32 * x, 32 * y, 0 , 0, al_map_rgba(0,0,255,255), 1.0);
                }
            }

            al_draw_filled_rectangle(player->x - p1_scroll.x, player->y - p1_scroll.y, 32 + player->x, 32 + player->y,al_map_rgb(255,0,255));

            al_flip_display();
        }

    }

    window_gracefully_quit("Quit END OF MAIN");
    return 0;
}

static void game_update_keyboard(ALLEGRO_EVENT *e){
    keyboard_map(e);
}
