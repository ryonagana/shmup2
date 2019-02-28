#include "states/GameStateManager.h"

CGameStateManager::CGameStateManager(){
    states =  std::vector<IGameState*>();
}

CGameStateManager::~CGameStateManager(){
    states.clear();
}

void CGameStateManager::InitStates(){

    for(auto s : this->states){
        s->Init();
        s->Start();
    }
}



bool CGameStateManager::addState(int id, IGameState *state){



    if(state != nullptr){
        if(states.size() == 0){
            states.push_back(std::move(state));
            states.back()->id = id;
            states.back()->active = false;
            return true;
        }

        states.push_back(std::move(state));
        states.back()->id = id;
        states.back()->active = false;

        return true;

    }

    return false;
}

IGameState *CGameStateManager::FindState(const int& id){
    auto f = std::find_if(this->states.begin(), states.end(), [&id](IGameState* &state)-> bool { return state->id == id; });
    return *f.base();
}

bool CGameStateManager::removeState(const int index){

   states.erase( std::remove(states.begin(), states.end(), index));

    return true;
}

IGameState *CGameStateManager::FindStateActive(){
    auto f = std::find_if(this->states.begin(), states.end(), [](IGameState* &state)-> bool { return state->active == true; });
    return *f.base();
}

IGameState *CGameStateManager::stateActive(){
    auto f = FindStateActive();

    if(f == nullptr){
        return nullptr;
    }

    return f;
}

bool CGameStateManager::SetStateActive(const int index, bool state){
    auto f = states.at(static_cast<size_t>(index));

    if(f == nullptr) return false;

    f->active = state;
    return true;
}

bool CGameStateManager::GetStateActive(const int index){
    auto f = states.at(static_cast<size_t>(index));

    if(f == nullptr) return false;
    return f->active;
}
