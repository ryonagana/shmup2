#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

#include "states/GameStateManager.h"
#include "gamestates/CMainGameState.h"
#include "gamestates/CMenuState.h"

class CEngine {
private:
    CGameStateManager stateManager;
    std::vector<IGameState*> stateList;
public:
    CEngine();
    IGameState *getState();
    void setState(int index);
    ~CEngine();
};
