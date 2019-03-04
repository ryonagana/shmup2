#include "CEngine.h"

CEngine::CEngine()
{
    stateList = std::vector<IGameState*>();
    stateList.reserve(10);

    stateList.push_back(new CMenuState());
    stateManager.addState(1, stateList.back());


    stateList.push_back(new CMainGameState());
    stateManager.addState(2, stateList.back());

    stateManager.SetStateActive(1, true);
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

CEngine::~CEngine()
{
    stateList.clear();
}
