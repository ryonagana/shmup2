#include "main.h"
#include "mouse.h"
#include "editor.h"
#include "config.h"
#include "menu.h"
#include "dir.h"
#include "states/GameStateManager.h"

#include "gamestates/CMainGameState.h"
#include "gamestates/CMenuState.h"
#include "states/IGameState.h"


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

    CGameStateManager manager;
    IGameState* mainGame = new CMainGameState();
    IGameState* menuGame = new CMenuState();

    manager.addState(0, mainGame);
    manager.addState(1, menuGame);

    manager.SetStateActive(1, true);

    manager.InitStates();




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

               manager.stateActive()->Update(&event);

               /*
               switch(game_state){
                    case GAMESTATE_SELECT_MAP_EDITOR:
                        al_flush_event_queue(get_window_queue());
                        menu_update(&menu_select_map_editor, &event);
                    break;
                    case GAMESTATE_SELECT_MAP:
                         al_flush_event_queue(get_window_queue());
                         menu_update(&menu_select_map, &event);
                    break;
                    case GAMESTATE_GAME:
                        spaceship_update(SHIP_P1);
                        spaceship_scrolling_update(player, &p1_camera, teste.map_width, teste.map_height);
                   break;

                   case GAMESTATE_MENU:
                       menu_update(&main_menu, &event);
                   break;

                   case GAMESTATE_EDITOR:
                       editor_update(&event);
                   break;
               }
               */

           }

           if(event.timer.source == get_window_actual_time()){
                set_window_time_ms(event.timer.count);

           }
       }


       if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE){
            al_acknowledge_resize(get_window_display());
       }




        if(config_get()->editor_mode.i_field){
            editor_update_input(&event);
        }


         manager.stateActive()->UpdateInput(&event);





        if(al_is_event_queue_empty(get_window_queue())){

            manager.stateActive()->Draw();

            /*
            switch(game_state){
                case GAMESTATE_SELECT_MAP_EDITOR:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    menu_draw(&menu_select_map_editor);
                break;
                case GAMESTATE_SELECT_MAP:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    menu_draw(&menu_select_map);
                break;
                case GAMESTATE_MENU:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    menu_draw(&main_menu);
                break;
                case GAMESTATE_GAME:
                    render_background_color(&teste);
                    render_tilemap(&teste, &p1_camera);
                    al_draw_bitmap(spr_player, player->x - p1_camera.x, player->y - p1_camera.y, 0);
                break;
                case GAMESTATE_EDITOR:
                    editor_render();
                break;
            }
            */

            al_flip_display();
        }

    }
    window_gracefully_quit("Quit END OF MAIN");
    return 0;
}



