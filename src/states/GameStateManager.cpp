#include "states/GameStateManager.h"

CGameStateManager::CGameStateManager(){
    states =  std::vector<GameState>();


}

CGameStateManager::~CGameStateManager(){
    states.clear();
}

void CGameStateManager::InitStates(){
    for(auto i = states.begin(); i != states.end();i++){
        i.base()->get()->Init();
    }

}

bool CGameStateManager::addState(const std::string &name, int id, GameState state)
{
    states.push_back(std::move(state));
    states.back().get()->name = name;
    states.back().get()->id = id;
    return true;
}





bool CGameStateManager::removeState(const int index){

   states.erase( std::remove(states.begin(), states.end(), index));

    return true;
}

IGameState *CGameStateManager::getStatebyIndex(int i){
    return this->states.at(static_cast<size_t>(i)).get();
}


IGameState *CGameStateManager::stateActive(){
    return active.get();
}

bool CGameStateManager::SetStateActive(const int index){
    //IGameState *f =  this->FindState(index);
   // return f == nullptr ? false : true;
}

