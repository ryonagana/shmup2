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
    this->ship = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(ship);
    spaceship_camera_init(&ship_camera, ship);

    this->ship_bmp = al_create_bitmap(32,32);
    al_set_target_bitmap(this->ship_bmp);
    al_clear_to_color(al_map_rgb(255,0,0));
    al_set_target_backbuffer(get_window_display());


}

void CMainGameState::Destroy()
{
}

void CMainGameState::Update(ALLEGRO_EVENT *e)
{
    UNUSED_PARAM(e);
     spaceship_update(SHIP_P1);
     spaceship_scrolling_update(this->ship, &this->ship_camera, this->engine->getLoadedLevel()->map_width, this->engine->getLoadedLevel()->map_width);
    return;
}

void CMainGameState::Draw()
{
    render_background_color(this->engine->getLoadedLevel());
    render_tilemap(this->engine->getLoadedLevel(), &this->ship_camera);
    al_draw_bitmap(this->ship_bmp, this->ship->x - ship_camera.x , this->ship->y - ship_camera.y,0);
    return;
}





void CMainGameState::HandleInput(ALLEGRO_EVENT *e)
{
    keyboard_map(e);
    return;
}
