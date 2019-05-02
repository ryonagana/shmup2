#include "gamestates/CMainGameState.h"
#include "tiles.h"

CMainGameState::CMainGameState() : CMainGameState(nullptr){
}

CMainGameState::CMainGameState(CEngine *parent) : engine(parent){

    level = nullptr;

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

    spaceship_start(ship, &ship_camera);


    this->ship_bmp = al_create_bitmap(32,32);
    al_set_target_bitmap(this->ship_bmp);
    al_clear_to_color(al_map_rgb(255,0,0));
    al_set_target_backbuffer(get_window_display());
    level = this->engine->getLoadedLevel();
    LOG("STARTING : %s", this->engine->getLoadedLevel()->mapname.c_str());
    render_start(level);





}

void CMainGameState::Destroy()
{
    spaceship_destroy();
    render_destroy();
}

void CMainGameState::Update(ALLEGRO_EVENT *e)
{
    UNUSED_PARAM(e);
    spaceship_update(SHIP_P1);
    spaceship_scrolling_update(this->ship, &this->ship_camera,this->engine->getLoadedLevel()->map_width, this->engine->getLoadedLevel()->map_width);


    static  Utils::CRect old_ship_pos = this->ship->rect;
    SPACESHIP_DIRECTION old_dir = ship->direction;


    for(int y = 0; y < level->map_width; y++){
        for(int x = 0; x < level->map_height;x++){
             TILE tile = level->map_layer[y][x];
             Utils::CRect r( TILE_SIZE * x, TILE_SIZE * y, TILE_SIZE, TILE_SIZE );

                 if(this->ship->rect.HasIntersection(r) && tile.id != NO_TILE ){
                    LOG("ID: %d Collision %d", tile.id, this->ship->flags.collision);

                    if(ship->direction != old_dir ){
                        this->ship->speed = 3.0f;
                    }else {
                        this->ship->speed = 0;
                    }

                 }else {

                 }
            }
    }

    if(this->ship->flags.collision){
        this->ship->speed = 0;
    }


     return;
}

void CMainGameState::Draw()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    //render_background_color(this->engine->getLoadedLevel());
    render_tilemap(this->engine->getLoadedLevel(), &this->ship_camera, this->ship);
    return;
}





void CMainGameState::HandleInput(ALLEGRO_EVENT *e)
{
    keyboard_update(e);
    return;
}
