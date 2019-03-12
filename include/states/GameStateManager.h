#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include <map>
#include "IGameState.h"
#include "states/NonMovable.h"
#include "shared.h"


class CGameStateManager {
private:
        std::vector< std::unique_ptr<IGameState> > states;
        IGameState *active;

        IGameState *findStateById(int id);
public:

    CGameStateManager();
    void InitStates(); //please call this after add states!

    bool addState(const std::string &name, int id, std::unique_ptr<IGameState> state);
    bool removeState(const int index);
    IGameState *stateActive();
    void SetStateActive(const int id);


    ~CGameStateManager();
};
