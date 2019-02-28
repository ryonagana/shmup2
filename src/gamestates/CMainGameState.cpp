#include "gamestates/CMainGameState.h"

void CMainGameState::Init()
{
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

CMainGameState::CMainGameState(){

}

CMainGameState::~CMainGameState() {

}



void CMainGameState::UpdateInput(ALLEGRO_EVENT *e)
{
}
