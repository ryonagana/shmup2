#pragma once
#include <iostream>
#include <functional>
#include <algorithm>
#include <memory>
#include "CEngine.h"
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


typedef  struct MENU_PARAM_CALLBACK {
    std::string name;
    std::string path;
}MENU_PARAM_CALLBACK;




class CEngine;

class CMenuState : public IGameState {

private:
    MENU main_menu;
    MENU menu_select_map;
    MENU menu_select_map_editor;
    std::string level_path;
    CDirectory dir;
    CEngine *engine;

    MENU_OPT_TYPE state;

    // callback to call an action opaque  callback inside static callback
    void menuMapDirCallbackF(MENU *menu, int id, const std::string name);

    // callbacks for the menu
    //please dont touch here if you dont know what are you doing..

     bool menuClickNewGame(int id); // is called when you click in "new game"
     bool menuClickEditor(int id); // is called when you click in "editor"
     bool menuClickQuit( int id); // is called when you click in "quit"
     bool menuClickMapList(int id); // a sub menu with map list
     bool menuClickMapListEditor( int id); // a sub menu with map list




     static int  readMapDirCallback(ALLEGRO_FS_ENTRY *dir, void *extra); // this is a  callback to list all map files inside "map" folder
     static int  readMapDirCallbackEditor(ALLEGRO_FS_ENTRY *dir, void *extra); // this is a  callback to list all map files inside "map" folder for editor
     static bool menuClickSelectMap(int id);

    // IGameState interface
public:



    CMenuState();
    CMenuState(CEngine *parent = nullptr);
    ~CMenuState() override;
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(ALLEGRO_EVENT *e) override;
    virtual void Draw() override;
    virtual void HandleInput(ALLEGRO_EVENT *e) override;


};
