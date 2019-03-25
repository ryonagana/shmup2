#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include <map>

#include "states/NonMovable.h"
#include "shared.h"
#include "IGameState.h"

class CEngine;

class CGameStateManager {
private:
        std::vector< std::shared_ptr<IGameState> > states;
        IGameState *active;

        IGameState *findStateById(int id);
        bool findAndRemoveById(int id);
public:

    CGameStateManager();
    void InitStates(); //please call this after add states!

    bool addState(const std::string &name, GameStateID id, std::shared_ptr<IGameState> state);
    bool removeState(const int id);
    IGameState *stateActive();
    void SetStateActive(const GameStateID id);
    void DestroyAllStates(void);


    ~CGameStateManager();
};
