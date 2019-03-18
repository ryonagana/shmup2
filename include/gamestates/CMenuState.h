#pragma once
#include <iostream>
#include <functional>
#include <algorithm>
#include <ctime>
#include <memory>
#include <string>
#include "CEngine.h"
#include "states/IGameState.h"
#include "menu.h"
#include "shared.h"
#include "window.h"
#include "level.h"
#include "dir.h"
#include "mouse.h"
#include "keyboard.h"
#include "text.h"
#include "Utils/CRandom.h"


enum class MENU_OPT_TYPE : uint32_t {
    MENU_OPT_NONE = 0,
    MENU_OPT_QUIT,
    MENU_OPT_NEW_GAME,
    MENU_OPT_EDITOR,
};


typedef  struct MENU_PARAM_CALLBACK {
    std::string name;
    std::string path;
    MENU_PARAM_CALLBACK(const std::string name, const std::string path){
        this->name = name;
        this->path = path;
    }
}MENU_PARAM_CALLBACK;


class CMenuState : public IGameState {

private:

    std::string level_path;
    CDirectory dir;
    CEngine *mainEngine;
    MENU_OPT_TYPE state;





    bool windowMainMenu;
    bool windowSelectMap;
    bool windowEditorMode;

    bool redraw;
    bool teste;

    // callback to call an action opaque  callback inside static callback
    void menuOpaqueCallbackDir(MENU *menu, int id, const std::string name);
    void menuOpaqueClickedLoadMap(MENU *menu, int index);




     static int  readMapDirCallback(ALLEGRO_FS_ENTRY *dir, void *extra); // this is a  callback to list all map files inside "map" folder
     static int  readMapDirCallbackEditor(ALLEGRO_FS_ENTRY *dir, void *extra); // this is a  callback to list all map files inside "map" folder for editor
     static bool menuClickSelectMap(int id);

    // IGameState interface
public:

    std::vector<MENU_PARAM_CALLBACK*> mapList;
    std::string mapSelected;

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
