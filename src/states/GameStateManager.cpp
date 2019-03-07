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
        s->Init();
        s->Start();
        s->active = false;
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

IGameState *CGameStateManager::FindStateActive(bool status){
    auto f = std::find_if(this->states.begin(), states.end(), [&status](IGameState* &state)-> bool { return state->active == status; });
    return *f.base();
}

IGameState *CGameStateManager::stateActive(){

    if(active == nullptr || states.size() <= 0 ){
        return nullptr;
    }
    return active;
}

bool CGameStateManager::SetStateActive(const int index, bool state){


    auto f = states.at(static_cast<size_t>(index));

    if(f == nullptr) return false;

    f->active = state;
    this->active = f;
    return true;
}

bool CGameStateManager::GetStateActive(const int index){
    auto f = states.at(static_cast<size_t>(index));

    if(f == nullptr) return false;
    return f->active;
}
