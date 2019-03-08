#include "CEngine.h"

CEngine::CEngine()
{
    stateList = std::vector<IGameState*>();
    stateList.reserve(10);
    loadedLevel = nullptr;


    stateList.push_back(new CMenuState(this));

    stateList.push_back(new CMainGameState(this));

    stateManager.addState(1, stateList[0]);
    stateManager.addState(2, stateList[1]);

    stateManager.SetStateActive(1);



}

IGameState *CEngine::getState()
{
    return stateManager.stateActive();
}

void CEngine::setState(int index)
{
    stateManager.SetStateActive(index);
    return;
}

LEVEL *CEngine::getLoadedLevel(){
    return loadedLevel;
}

CEngine::~CEngine()
{
    stateList.clear();
}

void CEngine::Start(){
   stateManager.InitStates();
}

