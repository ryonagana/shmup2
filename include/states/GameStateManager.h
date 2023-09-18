#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include <map>

#include "states/NonMovable.h"
#include "shared.h"
#include "IGameState.h"
#include "spaceship.h"

class CEngine;

using IGameStatePtr = std::shared_ptr<IGameState>;

class CGameStateManager {

public:

    CGameStateManager(CEngine& parent);
    //void InitStates(); //please call this after add states!

    bool addState(const std::string &name, std::shared_ptr<IGameState> state);
    bool removeState(const int id);
    IGameState *getActiveState();
    void SetStateActive(const std::string& name);
    void DestroyAllStates(void);
    void setWindowTitle(const std::string name);
    ~CGameStateManager();

private:

        CEngine &engine;
        std::unordered_map<std::string, IGameStatePtr> states;

        IGameState *active;

        IGameState *findStateById(const std::string &name);
        bool findAndRemoveById(int id);
};
