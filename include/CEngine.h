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
#include "gamestates/CMenuState.h"
#include "states/NonMovable.h"


class CEngine {
private:
    CGameStateManager stateManager;
    LEVEL *level;
    bool redraw;
    //TODO ENEMIES LIST
    //TODO POWERUP/COINS/GOODIES/LIFE/ITEMS LIST
    //TODO PARTICLE LIST

public:



    CEngine();
    ~CEngine();
    void Start();
    void End();
    IGameState *getState();
    void loadNewLevel(const std::string &mapname);
    void setLevel(LEVEL *level);
    void setState(const GameStateID id);
    CGameStateManager getStateManager();
    LEVEL *getLoadedLevel();

};
