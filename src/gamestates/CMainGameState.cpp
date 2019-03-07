#include "gamestates/CMainGameState.h"

CMainGameState::CMainGameState() : CMainGameState(nullptr){

}

CMainGameState::CMainGameState(CEngine *parent) : engine(parent){

}

CMainGameState::~CMainGameState(){

}

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





void CMainGameState::UpdateInput(ALLEGRO_EVENT *e)
{
}
