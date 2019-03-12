#include "states/GameStateManager.h"



IGameState *CGameStateManager::findStateById(int id)
{
    auto f = std::find_if(states.begin(), states.end(), [&id](const std::unique_ptr<IGameState> &state) -> bool {
            return state.get()->id == id;
    });

    return f->get();

}

CGameStateManager::CGameStateManager()
{
    states  = std::vector< std::unique_ptr<IGameState>>();

}

void CGameStateManager::InitStates()
{
    for(auto s = states.begin(); s != states.end(); s++){
            s.base()->get()->Start();
    }
}

bool CGameStateManager::addState(const std::string &name, int id, std::unique_ptr<IGameState> state)
{

    states.push_back( std::move(state) );
    states.back()->id = id;
    states.back()->name = name;
    return true;
}

bool CGameStateManager::removeState(const int index)
{
    //auto f = states.erase(states.begin(), states.end() + )
    return false;
}

IGameState *CGameStateManager::stateActive()
{
    return active;
}

void CGameStateManager::SetStateActive(const int id)
{
    auto f = findStateById(id);
    this->active = f;

}

CGameStateManager::~CGameStateManager(){

}
