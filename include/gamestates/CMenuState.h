#pragma once
#include <iostream>
#include "states/IGameState.h"
#include "menu.h"
#include "shared.h"
#include "window.h"
#include "level.h"
#include "dir.h"
#include "mouse.h"
#include "keyboard.h"

enum class MENU_OPT_TYPE : uint32_t {
    MENU_OPT_NONE = 0,
    MENU_OPT_QUIT,
    MENU_OPT_NEW_GAME,
    MENU_OPT_EDITOR,
};

class CMenuState : public IGameState {

private:
    MENU main_menu;
    MENU menu_select_map;
    MENU menu_select_map_editor;
    std::string level_path;
    CDirectory dir;


    // callbacks for the menu
    //please dont touch here if you dont know what are you doing..

    static bool main_menu_new_game_option(MENU *menu, int id); // is called when you click in "new game"
    static bool main_menu_editor_option(MENU *menu, int id); // is called when you click in "editor"
    static bool main_menu_quit_option(MENU *menu, int id); // is called when you click in "quit"
    static bool main_menu_select_map(MENU *menu, int id); // a sub menu with map list
    static bool main_menu_select_map_editor(MENU *menu, int id); // a sub menu with map list
    static int  map_dir_callback(ALLEGRO_FS_ENTRY *dir, void *extra); // this is a  callback to list all map files inside "map" folder
    static int  map_dir_callback_editor(ALLEGRO_FS_ENTRY *dir, void *extra); // this is a  callback to list all map files inside "map" folder for editor


    // IGameState interface
public:
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(ALLEGRO_EVENT *e) override;
    virtual void Draw() override;
    virtual void UpdateInput(ALLEGRO_EVENT *e) override;


};
