#include "main.h"
#include "mouse.h"
#include "editor.h"
#include "config.h"

static SPACESHIP *player =  NULL;
static CAMERA p1_camera;

static ALLEGRO_BITMAP *spr_player = NULL; //test

static void game_update_keyboard(ALLEGRO_EVENT *e);

int main()
{
    srand(time(NULL));
    window_init();

    player = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(player);

    spr_player = al_create_bitmap(32,32);
    al_set_target_bitmap(spr_player);
    al_clear_to_color(al_map_rgb(255,0,255));
    al_set_target_backbuffer(get_window_display());


    LEVEL teste;

    //level_init_default(&teste);
    //level_save(get_window_display(), &teste, "teste01.cbm", false);

    if(config_get()->editor_mode.i_field){

        if(!level_file_exists("mapa_teste.cbm")){

            window_gracefully_quit("LEVEL not loaded");
            return 0;
        }

        teste = *editor_load_path("mapa_teste.cbm");

    }else {
        if(!level_load(get_window_display(), &teste, "mapa_teste.cbm", false)){
            CRITICAL("level not loaded correctly, sorry");
            window_gracefully_quit("map not loaded");
            return 0;
        }
    }

    spaceship_camera_init(&p1_camera, player);







    //level_save(get_window_display(), )


    while(window_open()){
        ALLEGRO_EVENT event;

        al_wait_for_event(get_window_queue(), &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                        window_exit_loop();
        }

       if(event.type == ALLEGRO_EVENT_TIMER){
           if(event.timer.source == get_window_timer()){
               if(!config_get()->editor_mode.b_field){
                    spaceship_update(SHIP_P1);
                     spaceship_scrolling_update(player, &p1_camera, teste.map_width, teste.map_height);
               }else {
                    editor_update(&event);
              }



           }

           if(event.timer.source == get_window_actual_time()){
                set_window_time_ms(event.timer.count);

           }
       }


       if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
            al_acknowledge_resize(get_window_display());
       }


        game_update_keyboard(&event);
        mouse_update(&event);

        if(config_get()->editor_mode.i_field){
            editor_update_input(&event);
        }



        if(al_is_event_queue_empty(get_window_queue())){



            if(config_get()->editor_mode.i_field){

                editor_render();

            }else {
              render_background_color(&teste);
              render_tilemap(&teste, &p1_camera);
              al_draw_bitmap(spr_player, player->x - p1_camera.x, player->y - p1_camera.y, 0);
            }

            al_flip_display();
        }

    }

    window_gracefully_quit("Quit END OF MAIN");
    return 0;
}

static void game_update_keyboard(ALLEGRO_EVENT *e){
    keyboard_map(e);

}

