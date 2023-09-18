#include "states/GameStateManager.h"
#include "window.h"
#include "CEngine.h"


IGameState *CGameStateManager::findStateById(const std::string& name)
{
    auto f = states.find(name);

    if(f == states.end()){
        return NULL;
    }

    return f->second.get();

}

bool CGameStateManager::findAndRemoveById(int id)
{
    UNUSED_PARAM(id);
    return false;
}

CGameStateManager::CGameStateManager(CEngine &parent) : engine(parent)
{
    //states  = std::vector< std::shared_ptr<IGameState>>();

}



bool CGameStateManager::addState(const std::string &name, std::shared_ptr<IGameState> state){

    if(!state.get()){
        return false;
    }
    state->name = name;
    state->Init();
    states.insert({name, std::move(state)});
    return true;
}




bool CGameStateManager::removeState(const int id)
{
    UNUSED(id);
    //auto state = findStateById(id);

    //auto f = state.erase(states.begin(), states.end());
    return false;
}

IGameState *CGameStateManager::getActiveState()
{
    return active;
}



void CGameStateManager::SetStateActive(const std::string& name)
{

    auto f =  states.find(name);

    if(f == states.end()){
        return;
    }

    this->active = f->second.get();
    this->active->Start();
}

CGameStateManager::~CGameStateManager(){

}


/* this destroy is different for unitialize memory
 this must be used  when all states will not be used anymore
must be called before any memory free callings
it just unitialize states first and free internals
after this  you can free memory
calling this after free might cause  SIGSEGV, crashes, memory leaking
*/
void CGameStateManager::DestroyAllStates(){
        /*
        for(auto s = states.begin(); s != states.end(); s++){
                s.base()->get()->Destroy();
        }
        */
    for(auto& s : states){
        s.second->Destroy();
    }
}

void CGameStateManager::setWindowTitle(const std::string name)
{
    UNUSED(name);
    return;
    //set_window_title(name);
}
