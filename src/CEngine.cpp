#include "CEngine.h"

CEngine::CEngine()
{
    stateList = std::vector<IGameState*>();
    stateList.reserve(10);
    loadedLevel = nullptr;

    stateList.push_back(new CMenuState(this));
    stateManager.addState(1, stateList.back());


    stateList.push_back(new CMainGameState(this));
    stateManager.addState(2, stateList.back());

    stateManager.InitStates();
    this->setState(0);



}

IGameState *CEngine::getState()
{
    return stateManager.stateActive();
}

void CEngine::setState(int index)
{
    stateManager.SetStateActive(index, true);
}

LEVEL *CEngine::getLoadedLevel(){
    return loadedLevel;
}

CEngine::~CEngine()
{
    stateList.clear();
}

