#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "level.h"
#include "states/GameStateManager.h"
#include "gamestates/CMainGameState.h"
#include "states/NonMovable.h"

#include "Utils/CWindow.h"

class CEngine {
private:
    CGameStateManager stateManager;
    LEVEL loadedLevel;
    bool redraw;
    CWindow *mainWindow;
    //TODO ENEMIES LIST
    //TODO POWERUP/COINS/GOODIES/LIFE/ITEMS LIST
    //TODO PARTICLE LIST

public:



    CEngine(CWindow *win);
    ~CEngine();
    void Start();
    IGameState *getState();
    CWindow *getRenderWindow();
    void setMainWindow(CWindow *win);
    void loadNewLevel(const std::string &mapname);
    void setState(const GameStateID id);
    CGameStateManager getStateManager();
    LEVEL *getLoadedLevel();

};
