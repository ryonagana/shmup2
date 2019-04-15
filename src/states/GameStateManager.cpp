#include "states/GameStateManager.h"
//#include "window.h"


IGameState *CGameStateManager::findStateById(int id)
{
    auto f = std::find_if(states.begin(), states.end(), [&id](const std::shared_ptr<IGameState> &state) -> bool {
            return state.get()->id == id;
    });

    return f->get();

}

bool CGameStateManager::findAndRemoveById(int id)
{
    UNUSED_PARAM(id);
    return false;
}

CGameStateManager::CGameStateManager()
{
    states  = std::vector< std::shared_ptr<IGameState>>();

}

void CGameStateManager::InitStates()
{
    for(auto s = states.begin(); s != states.end(); s++){
            s.base()->get()->Start();
    }
}



bool CGameStateManager::addState(const std::string &name, GameStateID id, std::shared_ptr<IGameState> state){
    states.push_back( std::move(state) );
    states.back()->id = static_cast<int>(id);
    states.back()->stateId = id;
    states.back()->name = name;
    states.back()->Init();
    return true;
}




bool CGameStateManager::removeState(const int id)
{
    //auto state = findStateById(id);


    //auto f = states.erase(states.begin(), states.end() + )
    return false;
}

IGameState *CGameStateManager::stateActive()
{
    return active;
}



void CGameStateManager::SetStateActive(const GameStateID id)
{
    auto f = findStateById( static_cast<int>(id));
    this->active = f;

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
        for(auto s = states.begin(); s != states.end(); s++){
                s.base()->get()->Destroy();
        }
}

void CGameStateManager::setWindowTitle(const std::string name)
{
    //set_window_title(name);
}
