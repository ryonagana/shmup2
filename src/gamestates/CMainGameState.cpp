#include "gamestates/CMainGameState.h"

CMainGameState::CMainGameState() : CMainGameState(nullptr){

}

CMainGameState::CMainGameState(CEngine *parent) : engine(parent){




}

CMainGameState::~CMainGameState(){

}

void CMainGameState::Init()
{
    this->ship = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(ship);
    spaceship_camera_init(&ship_camera, ship);

    if(this->engine->getLoadedLevel()  == nullptr)
    {
        al_show_native_message_box(get_window_display(), "Error: Map Not Loaded!", "Map Not Loaded", "the map file was not found or corrupted", "Fuck You!",0);
        LOG("map file not loaded -- aborting all operation!");
        window_exit_loop();
        return;
    }
}

void CMainGameState::Start()
{
}

void CMainGameState::Destroy()
{
}

void CMainGameState::Update(ALLEGRO_EVENT *e)
{
    return;
}

void CMainGameState::Draw()
{
    al_clear_to_color(al_map_rgb(255,0,0));

    return;
}





void CMainGameState::UpdateInput(ALLEGRO_EVENT *e)
{
}
