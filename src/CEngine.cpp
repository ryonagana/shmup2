#include "CEngine.h"
#include "states/IGameState.h"
#include "gamestates/CMenuState.h"
#include "gamestates/CEditorState.h"

using GameState = std::unique_ptr<IGameState>;

CEngine::CEngine() : loadedLevel(nullptr)
{

   // menuState = std::make_unique<IGameState>();

   // stateManager.addState("Menu",1, menuState);



    stateManager.addState("Menu"  , GameStateID::Menu , std::make_shared<CMenuState>(this));
    stateManager.addState("Game"  , GameStateID::MainGame, std::make_shared<CMainGameState>(this));
    stateManager.addState("Editor", GameStateID::Editor, std::make_shared<CEditorState>(this));

    stateManager.SetStateActive(GameStateID::Menu);

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
    if(this->loadedLevel == nullptr) this->loadedLevel = new LEVEL;

    level_load(this->loadedLevel, mapname);
}

void CEngine::setState(const GameStateID id)
{
    stateManager.SetStateActive(id);
    stateManager.stateActive()->Start();
    return;
}

CGameStateManager CEngine::getStateManager()
{
    return this->stateManager;
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

void CEngine::End()
{
    if(this->loadedLevel != nullptr) delete this->loadedLevel;
    this->loadedLevel = nullptr;
}

