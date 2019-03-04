#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include "IGameState.h"




class CGameStateManager {
private:
        std::vector<IGameState*> states;
        IGameState *active;
public:

    CGameStateManager();
    void InitStates(); //please call this before add states!
    bool addState(int id, IGameState *state);
    bool removeState(const int index);
    IGameState* FindState(const int &id);
    IGameState* FindStateActive(bool status);
    IGameState *stateActive();
    bool SetStateActive(const int index, bool state);
    bool GetStateActive(const int index);

    ~CGameStateManager();
};
