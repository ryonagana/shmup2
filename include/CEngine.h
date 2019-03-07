#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include "level.h"
#include "states/GameStateManager.h"
#include "gamestates/CMainGameState.h"
#include "gamestates/CMenuState.h"

class CEngine {
private:
    CGameStateManager stateManager;
    std::vector<IGameState*> stateList;
    LEVEL *loadedLevel;
    //TODO ENEMIES LIST
    //TODO POWERUP/COINS/GOODIES/LIFE/ITEMS LIST
    //TODO PARTICLE LIST
public:
    CEngine();
    IGameState *getState();
    void setState(int index);
    LEVEL *getLoadedLevel();
    ~CEngine();
};
