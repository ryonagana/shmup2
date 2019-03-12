#include "CEngine.h"
#include "states/IGameState.h"
using GameState = std::unique_ptr<IGameState>;

CEngine::CEngine()
{

    loadedLevel = nullptr;
    //stateManager.addState("Teste",0, std::unique_ptr<GameState>(new CMenuState(nullptr)));
    //stateManager.addState("Teste 2",1, std::std::unique_ptr<GameState>(new CMainGameState(nullptr)));

    if(!stateManager.SetStateActive(1)){
        std::stringstream msg;
        msg << "State Not Loaded Correctly! Sorry" << std::endl;
        WARN(msg.str());
        al_show_native_message_box(get_window_display(), "Error!", "Error:", msg.str().c_str(),"OK", 0);
    }



}

IGameState *CEngine::getState()
{
    return stateManager.getStatebyIndex(0);
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

}

void CEngine::Start(){
   stateManager.InitStates();
}

