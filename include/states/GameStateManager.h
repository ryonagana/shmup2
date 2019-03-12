#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include "IGameState.h"
#include "states/NonMovable.h"
#include "shared.h"




class CGameStateManager {
private:
        std::vector<GameState> states;
        GameState active;
public:

    CGameStateManager();
    void InitStates(); //please call this before add states!

    bool addState(const std::string &name = "Generic State", int id = 1,GameState state = nullptr);
    bool removeState(const int index);
    IGameState *stateActive();
    IGameState *getStatebyIndex(int i);
    bool SetStateActive(const int index);


    ~CGameStateManager();
};
