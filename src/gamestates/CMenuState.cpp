#include "gamestates/CMenuState.h"


bool  CMenuState::main_menu_new_game_option(MENU *menu, int id){
    UNUSED_PARAM(id);
    UNUSED_PARAM(menu);

    return false;
}


bool  CMenuState::main_menu_editor_option(MENU *menu, int id){
    UNUSED_PARAM(id);
    UNUSED_PARAM(menu);

    return false;
}

bool  CMenuState::main_menu_quit_option(MENU *menu, int id){
    UNUSED_PARAM(id);
    UNUSED_PARAM(menu);
    window_exit_loop();
    return false;
}



bool CMenuState::main_menu_select_map(MENU *menu, int id)
{

    std::string menu_name = menu->entries[id].menu;
    menu_name += ".cbm";


    return false;
}

bool CMenuState::main_menu_select_map_editor(MENU *menu, int id){
    std::string menu_name = menu->entries[id].menu;
    menu_name += ".cbm";

   return false;
}


/* LOAD ALL MAPS */
int CMenuState::map_dir_callback(ALLEGRO_FS_ENTRY *dir, void *extra){
    static int i = 0;
    ALLEGRO_PATH *path = al_create_path(al_get_fs_entry_name(dir));

    std::string menu_name = al_get_path_basename(path);
    //menu_add_entry(&this->menu_select_map,i++, menu_name.c_str(), MENU_TYPE_SIMPLE, this->main_menu_select_map);
    al_destroy_path(path);
    return ALLEGRO_FOR_EACH_FS_ENTRY_OK;
}

int  CMenuState::map_dir_callback_editor(ALLEGRO_FS_ENTRY *dir, void *extra){
    static int i = 0;
    ALLEGRO_PATH *path = al_create_path(al_get_fs_entry_name(dir));

    std::string menu_name = al_get_path_basename(path);
    //menu_add_entry(&menu_select_map_editor,i++, menu_name.c_str(), MENU_TYPE_SIMPLE,&main_menu_select_map_editor);
    al_destroy_path(path);
    return ALLEGRO_FOR_EACH_FS_ENTRY_OK;
}

void CMenuState::Init()
{

    dir.SetPath("map");

    menu_create(&main_menu, 5);
    menu_add_entry(&main_menu, 1, "NEW GAME (ALPHA)", MENU_TYPE_SIMPLE, &main_menu_new_game_option);
    menu_add_entry(&main_menu, 2, "EDITOR", MENU_TYPE_SIMPLE, &main_menu_editor_option);
    menu_add_entry(&main_menu, 3,  "QUIT", MENU_TYPE_SIMPLE, &main_menu_quit_option);


    menu_create(&menu_select_map,10);
    al_for_each_fs_entry(dir.getEntry(), &this->map_dir_callback, nullptr);


    menu_create(&menu_select_map_editor,10);
    al_for_each_fs_entry(dir.getEntry(), &map_dir_callback_editor, nullptr);

}

void CMenuState::Start()
{
}

void CMenuState::Destroy()
{
}

void CMenuState::Update(ALLEGRO_EVENT *e)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    menu_update(&this->main_menu, e);
}

void CMenuState::UpdateInput(ALLEGRO_EVENT *e){
    mouse_update(e);
}

void CMenuState::Draw()
{
    menu_draw(&main_menu);
}
