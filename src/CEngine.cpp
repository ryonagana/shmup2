#include "CEngine.h"

CEngine::CEngine()
{
    stateList = std::vector<IGameState*>();
    stateList.reserve(10);
    loadedLevel = nullptr;


    stateManager.addState(0, new CMenuState(nullptr));
    stateManager.addState(1, new CMainGameState(nullptr));

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
    stateList.clear();
}

void CEngine::Start(){
   stateManager.InitStates();
}

