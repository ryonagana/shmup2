#include "main.h"
#include "mouse.h"
#include "editor.h"
#include "config.h"
#include "menu.h"
#include "dir.h"
#include "states/GameStateManager.h"

#include "gamestates/CMainGame.h"
#include "states/IGameState.h"

typedef enum {
    MENU_OPT_NONE = 0,
    MENU_OPT_QUIT,
    MENU_OPT_NEW_GAME,
    MENU_OPT_EDITOR,


}MENU_OPT_TYPE;


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

static MENU main_menu;
static MENU menu_select_map;
static MENU menu_select_map_editor;
static GAMESTATE game_state = GAMESTATE_MENU;

static LEVEL teste;

static void game_update_keyboard(ALLEGRO_EVENT *e);


bool  main_menu_new_game_option(MENU *menu, int id){
    UNUSED_PARAM(id);
    UNUSED_PARAM(menu);
    game_state = GAMESTATE_SELECT_MAP;
    return false;
}


bool  main_menu_editor_option(MENU *menu, int id){
    UNUSED_PARAM(id);
    UNUSED_PARAM(menu);
    game_state = GAMESTATE_SELECT_MAP_EDITOR;
    return false;
}

bool  main_menu_quit_option(MENU *menu, int id){
    UNUSED_PARAM(id);
    UNUSED_PARAM(menu);
    window_exit_loop();
    return false;
}



bool main_menu_select_map(MENU *menu, int id)
{

    std::string menu_name = menu->entries[id].menu;
    menu_name += ".cbm";

    //printf("id: %d name: %s", id, menu->entries[id].menu);

    if(!level_file_exists(menu_name.c_str())){
        al_show_native_message_box(get_window_display(), "Error!", "Missing Map!", "Missong Map tp Load!", nullptr, 0);
        return false;
    }

    level_load(get_window_display(), &teste, menu_name.c_str(), false);

    if(teste.valid_file){
        game_state = GAMESTATE_GAME;
        return true;
    }

    game_state = GAMESTATE_MENU;
    return true;
}

bool main_menu_select_map_editor(MENU *menu, int id){
    std::string menu_name = menu->entries[id].menu;
    menu_name += ".cbm";

    //printf("id: %d name: %s", id, menu->entries[id].menu);

    if(!level_file_exists(menu_name.c_str())){
        al_show_native_message_box(get_window_display(), "Error!", "Missing Map!", "Missong Map tp Load!", nullptr, 0);
        return false;
    }

    editor_load_path(menu_name.c_str());
    //level_load(get_window_display(), &teste, menu_name.c_str(), false);


    game_state = GAMESTATE_EDITOR;
}



/* LOAD ALL MAPS */
int  map_dir_callback(ALLEGRO_FS_ENTRY *dir, void *extra){
    static int i = 0;
    ALLEGRO_PATH *path = al_create_path(al_get_fs_entry_name(dir));

    std::string menu_name = al_get_path_basename(path);
    menu_add_entry(&menu_select_map,i++, menu_name.c_str(), MENU_TYPE_SIMPLE,&main_menu_select_map);
    al_destroy_path(path);
    return ALLEGRO_FOR_EACH_FS_ENTRY_OK;
}

int  map_dir_callback_editor(ALLEGRO_FS_ENTRY *dir, void *extra){
    static int i = 0;
    ALLEGRO_PATH *path = al_create_path(al_get_fs_entry_name(dir));

    std::string menu_name = al_get_path_basename(path);
    menu_add_entry(&menu_select_map_editor,i++, menu_name.c_str(), MENU_TYPE_SIMPLE,&main_menu_select_map_editor);
    al_destroy_path(path);
    return ALLEGRO_FOR_EACH_FS_ENTRY_OK;
}


int main(int  argc, char **argv)
{
    srand(time(nullptr));
    window_init();
    menu_init();
    player = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(player);

    CGameStateManager manager;
    IGameState* mainGame = new CMainGame();
    IGameState* menuGame = new CMainGame();

    manager.addState(0, mainGame);
    manager.addState(1, menuGame);

    manager.SetStateActive(1, true);

    manager.InitStates();

    CDirectory dir("map");


    spr_player = al_create_bitmap(32,32);
    al_set_target_bitmap(spr_player);
    al_clear_to_color(al_map_rgb(255,0,255));
    al_set_target_backbuffer(get_window_display());




    menu_create(&main_menu, 5);
    menu_add_entry(&main_menu, MENU_OPT_NEW_GAME, "NEW GAME (ALPHA)", MENU_TYPE_SIMPLE, &main_menu_new_game_option);
    menu_add_entry(&main_menu, MENU_OPT_EDITOR, "EDITOR", MENU_TYPE_SIMPLE, &main_menu_editor_option);
    menu_add_entry(&main_menu, MENU_OPT_QUIT,  "QUIT", MENU_TYPE_SIMPLE, &main_menu_quit_option);


    menu_create(&menu_select_map,10);
    al_for_each_fs_entry(dir.getEntry(), &map_dir_callback, nullptr);


    menu_create(&menu_select_map_editor,10);
    al_for_each_fs_entry(dir.getEntry(), &map_dir_callback_editor, nullptr);


    spaceship_camera_init(&p1_camera, player);

    while(window_open()){
        ALLEGRO_EVENT event;

        al_wait_for_event(get_window_queue(), &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                        game_state = GAMESTATE_MENU;
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



        game_update_keyboard(&event);
        mouse_update(&event);




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

static void game_update_keyboard(ALLEGRO_EVENT *e){
    keyboard_map(e);

}


