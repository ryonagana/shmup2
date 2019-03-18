#include "CEngine.h"
#include "states/IGameState.h"
#include "gamestates/CMenuState.h"
#include "gamestates/CEditorState.h"

using GameState = std::unique_ptr<IGameState>;

CEngine::CEngine()
{

   // menuState = std::make_unique<IGameState>();

   // stateManager.addState("Menu",1, menuState);


    stateManager.addState("Menu"  ,1, std::make_shared<CMenuState>(this));
    stateManager.addState("Game"  ,2, std::make_shared<CMainGameState>(this));
    stateManager.addState("Editor",3, std::make_shared<CEditorState>(this));

    stateManager.SetStateActive(1);

    stateManager.InitStates();

    redraw = false;
    //stateManager.addState("Menu",1, std::make_unique<IGameState>(new  CMainGameState(nullptr)));

    //stateManager.addState("Teste",0, std::unique_ptr<GameState>(new CMenuState(nullptr)));
    //stateManager.addState("Teste 2",1, std::std::unique_ptr<GameState>(new CMainGameState(nullptr)));

    /*
    if(!stateManager.SetStateActive(1)){
        std::stringstream msg;
        msg << "State Not Loaded Correctly! Sorry" << std::endl;
        WARN(msg.str());
        al_show_native_message_box(get_window_display(), "Error!", "Error:", msg.str().c_str(),"OK", 0);
    }
    */



}

IGameState *CEngine::getState()
{
    return stateManager.stateActive();
}

void CEngine::loadNewLevel(const std::string &mapname)
{
    level_load(get_window_display(), &this->loadedLevel, mapname.c_str(), false);
}

void CEngine::setState(int index)
{
    stateManager.SetStateActive(index);
    stateManager.stateActive()->Start();
    return;
}

LEVEL *CEngine::getLoadedLevel(){
    return &loadedLevel;
}

CEngine::~CEngine()
{

}

void CEngine::Start(){
   stateManager.InitStates();
}

