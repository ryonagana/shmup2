#include <stdio.h>
#include "window.h"
#include "keyboard.h"
#include "spaceship.h"


int main()
{
    window_init();

    struct spaceship *player = spaceship_get_player(SHIP_P1);


    while(window_open()){
        ALLEGRO_EVENT event;

        al_wait_for_event(get_window_queue(), &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                        window_exit_loop();
        }

       if(event.type == ALLEGRO_EVENT_TIMER){
           if(event.timer.source == get_window_timer()){
               spaceship_update(SHIP_P1);
               printf("%lld\n", get_window_time_ms());

               if(get_window_time_ms() > (get_window_time_ms() + 80) ){
                   printf("CHEGOU!!");
               }

           }

           if(event.timer.source == get_window_actual_time()){
                set_window_time_ms(event.timer.count);

           }
       }

       if(event.type == ALLEGRO_EVENT_KEY_UP){
            keyboard_key_up(&event);
             spaceship_keys_handle_up(SHIP_P1);
       }

       if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            keyboard_key_down(&event);
             spaceship_keys_handle_down(SHIP_P1);


       }


       if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
            al_acknowledge_resize(get_window_display());
       }


        if(al_is_event_queue_empty(get_window_queue())){
            al_clear_to_color(al_map_rgb(0,0,0));

            al_draw_filled_rectangle(player->x, player->y, 32 + player->x, 32 + player->y,al_map_rgb(255,0,0));

            al_flip_display();
        }

    }
    window_close();
    return 0;
}
