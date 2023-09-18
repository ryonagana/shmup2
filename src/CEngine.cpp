#include "CEngine.h"
#include "states/IGameState.h"
#include "gamestates/CMenuState.h"
#include "gamestates/CEditorState.h"

using GameState = std::unique_ptr<IGameState>;

CEngine::CEngine(GameWindow &gw) : stateManager(*this),
                                   gameWindow(gw)
{


}

IGameState *CEngine::getState()
{
    return stateManager.getActiveState();
}

void CEngine::loadNewLevel(const std::string &mapname)
{
    if(this->level == nullptr) return;
    //clear the map before load
    level_init_default(this->level);

    level_load(this->level, mapname);
}

void CEngine::setLevel(LEVEL *level)
{
    this->level = level;
}

void CEngine::setState(const std::string& name)
{
    stateManager.SetStateActive(name);
    stateManager.getActiveState()->Start();
    return;
}

CGameStateManager CEngine::getStateManager()
{
    return this->stateManager;
}

LEVEL *CEngine::getLoadedLevel(){
    return level;
}

CEngine::~CEngine()
{

      delete[] this->level;
}

void CEngine::Start(){
    init_path();


    this->level = new LEVEL;

#if 0
    stateManager.SetStateActive(GameStateID::Menu);
#else
    loadNewLevel("t1.cbm");
    stateManager.SetStateActive("Game");
#endif

    redraw = false;



    stateManager.addState("Menu",  std::make_shared<CMenuState>(this));
    stateManager.addState("Game",  std::make_shared<CMainGameState>(this));
    stateManager.addState("Editor",std::make_shared<CEditorState>(this));


    stateManager.SetStateActive("Game");
}

void CEngine::Loop()
{
#if 1
    while(gameWindow.isWindowOpen()){
        ALLEGRO_EVENT e;
        al_wait_for_event(gameWindow.getQueue(),&e);

        if(redraw && al_event_queue_is_empty(gameWindow.getQueue())){
            redraw = false;
            al_clear_to_color(al_map_rgb(255,0,0));
            stateManager.getActiveState()->Draw();
            al_flip_display();
        }

        if(e.type == ALLEGRO_EVENT_TIMER){
            stateManager.getActiveState()->Update(&e);
            redraw = true;
        }

        stateManager.getActiveState()->HandleInput(&e);
        stateManager.getActiveState()->WindowHandlerUpdate(&e);
    }
#endif
}

void CEngine::End()
{
    if(this->level != nullptr) delete this->level;
    this->level = nullptr;
}

