#include "CEngine.h"
#include "states/IGameState.h"
#include "gamestates/CMenuState.h"
#include "gamestates/CEditorState.h"

using GameState = std::unique_ptr<IGameState>;

CEngine::CEngine(CWindow *win)
{
    setMainWindow(win);

   // stateManager.addState("Menu"  , GameStateID::Menu , std::make_shared<CMenuState>(this));
   stateManager.addState("Game"  , GameStateID::MainGame, std::make_shared<CMainGameState>(this));
   // stateManager.addState("Editor", GameStateID::Editor, std::make_shared<CEditorState>(this));

   stateManager.SetStateActive(GameStateID::MainGame);
   stateManager.InitStates();


}

IGameState *CEngine::getState()
{
    return stateManager.stateActive();
}

CWindow *CEngine::getRenderWindow()
{
    return mainWindow;
}

void CEngine::setMainWindow(CWindow *win)
{
    mainWindow = win;
    return;
}

void CEngine::loadNewLevel(const std::string &mapname)
{
    level_load(&this->loadedLevel, mapname);
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
    return &loadedLevel;
}

CEngine::~CEngine()
{

}

void CEngine::Start(){
   stateManager.InitStates();
}

