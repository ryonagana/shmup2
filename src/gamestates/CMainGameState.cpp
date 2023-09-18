#include "gamestates/CMainGameState.h"
#include "tiles.h"

CMainGameState::CMainGameState() : CMainGameState(nullptr){
    hasCollided = false;
}

CMainGameState::CMainGameState(CEngine *parent) : engine(parent){

    level = nullptr;
    hasCollided = false;

    ships.reserve(2);
    ships.resize(2);

    for(int i = 0; i < 2 ;i++){
        SPACESHIP *s = new SPACESHIP;
        spaceship_set_default_flags(s);
        spaceship_camera_init(&ship_camera, s);
        spaceship_start(s, &ship_camera);
        ships.push_back(std::move(s));

    }

}

CMainGameState::~CMainGameState(){


}

void CMainGameState::Init()
{

    level = this->engine->getLoadedLevel();
    LOG("STARTING : %s", this->engine->getLoadedLevel()->mapname.c_str());
    render_start(level);

}

void CMainGameState::Start()
{







}

void CMainGameState::Destroy()
{
    for(auto& s : this->ships){
        spaceship_destroy(s);
    }

    render_destroy();
}

void CMainGameState::Update(ALLEGRO_EVENT *e)
{

    UNUSED(e);
#if 0
    spaceship_update(SHIP_P1);
    spaceship_scrolling_update(this->ship, &this->ship_camera,this->engine->getLoadedLevel()->map_width, this->engine->getLoadedLevel()->map_width);

    int tile_x = (static_cast<int>(ship->x) / TILE_SIZE) >= 0 ?  (static_cast<int>(ship->x) / TILE_SIZE) : 0;
    int tile_y = (static_cast<int>(ship->y) / TILE_SIZE) >= 0 ?  (static_cast<int>(ship->y) / TILE_SIZE) : 0;

    TILE tile = this->level->map_layer[tile_y][tile_x];
    TILE_ID tile_id = static_cast<TILE_ID>(tile.id);

    Utils::CRect tile_coll = {static_cast<float>(tile_x * TILE_SIZE), static_cast<float>(tile_y * TILE_SIZE), TILE_SIZE, TILE_SIZE };


    tile_coll.Update();


    if(tile_id != NO_TILE){

        Utils::CRect::RectangleSide collision_side = ship->rect.HasIntersection(tile_coll);

        //printf("%d - tile_x: %d  tile_y: %d\n",  collision_side, tile_x, tile_y);
    }

    /*
    if( (ship->rect.X() < 0) || ( (ship->rect.X() + TILE_SIZE) > window_get_width()) ||  (ship->rect.HasIntersection(collision)    && tile_id != NO_TILE)){
        ship->x = collision.Left() - ship->rect.W();
    }

    if( (ship->rect.Y() < 0) || ( (ship->rect.Y() + TILE_SIZE) > window_get_height()) ||  (ship->rect.HasIntersection(collision)    && tile_id != NO_TILE)){
        ship->y = collision.Bottom() - ship->rect.H();
    }
    */

    //printf("%.2f, %.2f\n\n", collision.X(), collision.Y());
#endif


}

void CMainGameState::Draw()
{

    render_background_color(this->engine->getLoadedLevel());
    render_tilemap(this->engine->getLoadedLevel(), &this->ship_camera, this->ships[0]);
    al_draw_textf(GameWindow::getInstance().getDebugFont(),al_map_rgb(255,0,255),0,0,0,"TEST TIMER: %d", sx);
    return;
}

void CMainGameState::WindowHandlerUpdate(ALLEGRO_EVENT *e)
{
    if(e->type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        engine->End();
        engine->getWindow().setWindow(false);
    }
}


void CMainGameState::HandleInput(ALLEGRO_EVENT *e)
{
    keyboard_update(e);
    return;
}
