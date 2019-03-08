#include "states/GameStateManager.h"

CGameStateManager::CGameStateManager(){
    states =  std::vector<IGameState*>();
    active = nullptr;

}

CGameStateManager::~CGameStateManager(){
    states.clear();
}

void CGameStateManager::InitStates(){

    for(auto s : this->states){
        s->Start();
    }
}



bool CGameStateManager::addState(int id, IGameState *state){
    if(state == nullptr) return false;
    states.push_back(std::move(state));
    states.back()->id = id;
    states.back()->active = false;
    states.back()->Init();
    return true;
}

IGameState *CGameStateManager::FindState(const int& id){
    auto f = std::find_if(this->states.begin(), this->states.end(), [&id](IGameState* &state)-> bool { return state->id == id; });
    return *f.base();
}

bool CGameStateManager::removeState(const int index){

   states.erase( std::remove(states.begin(), states.end(), index));

    return true;
}



IGameState *CGameStateManager::stateActive(){
    return active;
}

bool CGameStateManager::SetStateActive(const int index){
    auto f = states.at(index);
    this->active = f;
    return f == nullptr ? false : true;
}

