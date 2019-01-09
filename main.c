#include "main.h"


static SPACESHIP *player =  NULL;
static CAMERA p1_scroll;

static ALLEGRO_BITMAP *spr_player = NULL; //test

static void game_update_keyboard(ALLEGRO_EVENT *e);

int main()
{
    window_init();

    player = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(player);

    spr_player = al_create_bitmap(32,32);
    al_set_target_bitmap(spr_player);
    al_clear_to_color(al_map_rgb(255,0,255));
    al_set_target_backbuffer(get_window_display());


    LEVEL teste;
    level_init_default(&teste);
    level_save(get_window_display(), &teste, "teste01.cbm", false);


    if(!level_load(get_window_display(), &teste, "teste01.cbm", false)){
        CRITICAL("level not loaded correctly, sorry");
    }

     spaceship_scrolling_update(player, &p1_scroll);

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




              render_background_color(&teste);
              render_tilemap(&teste, &p1_scroll);


             al_draw_bitmap(spr_player, player->x - p1_scroll.x, player->y - p1_scroll.y, 0);
            //al_draw_filled_rectangle(player->x - p1_scroll.x, player->y - p1_scroll.y, 32 + player->x, 32 + player->y,al_map_rgb(255,0,255));

            al_flip_display();
        }

    }

    window_gracefully_quit("Quit END OF MAIN");
    return 0;
}

static void game_update_keyboard(ALLEGRO_EVENT *e){
    keyboard_map(e);
}


