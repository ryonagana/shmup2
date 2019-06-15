#include "gamestates/CMainGameState.h"
#include "tiles.h"

CMainGameState::CMainGameState() : CMainGameState(nullptr){
    hasCollided = false;
}

CMainGameState::CMainGameState(CEngine *parent) : engine(parent){

    level = nullptr;
    hasCollided = false;

}

CMainGameState::~CMainGameState(){

}

void CMainGameState::Init()
{

    this->ship = spaceship_get_player(SHIP_P1);
    spaceship_set_default_flags(ship);
    spaceship_camera_init(&ship_camera, ship);

    spaceship_start(ship, &ship_camera);

    ship->x = this->engine->getLoadedLevel()->player_pos.x;
    ship->y = this->engine->getLoadedLevel()->player_pos.y;


    this->ship_bmp = al_create_bitmap(32,32);
    al_set_target_bitmap(this->ship_bmp);
    al_clear_to_color(al_map_rgb(255,0,0));
    al_set_target_backbuffer(get_window_display());
    level = this->engine->getLoadedLevel();
    LOG("STARTING : %s", this->engine->getLoadedLevel()->mapname.c_str());
    render_start(level);
    font = al_create_builtin_font();

}

void CMainGameState::Start()
{







}

void CMainGameState::Destroy()
{
    spaceship_destroy();
    render_destroy();
}

void CMainGameState::Update(ALLEGRO_EVENT *e)
{
    spaceship_update(SHIP_P1);
    spaceship_scrolling_update(this->ship, &this->ship_camera,this->engine->getLoadedLevel()->map_width, this->engine->getLoadedLevel()->map_width);

}

void CMainGameState::Draw()
{

    render_background_color(this->engine->getLoadedLevel());
    render_tilemap(this->engine->getLoadedLevel(), &this->ship_camera, this->ship);
     al_draw_textf(font,al_map_rgb(255,0,255),0,0,0,"TEST TIMER: %d", sx);
    return;
}





void CMainGameState::HandleInput(ALLEGRO_EVENT *e)
{
    keyboard_update(e);
    return;
}
