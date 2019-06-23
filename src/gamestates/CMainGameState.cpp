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

    int tile_x = (static_cast<int>(ship->x) / TILE_SIZE) >= 0 ?  (static_cast<int>(ship->x) / TILE_SIZE) : 0;
    int tile_y = (static_cast<int>(ship->y) / TILE_SIZE) >= 0 ?  (static_cast<int>(ship->y) / TILE_SIZE) : 0;

    TILE tile = this->level->map_layer[tile_y][tile_x];
    TILE_ID tile_id = static_cast<TILE_ID>(tile.id);

    Utils::CRect tile_coll = {static_cast<float>(tile_x * TILE_SIZE), static_cast<float>(tile_y * TILE_SIZE), TILE_SIZE, TILE_SIZE };

    tile_coll.Update();


    if(tile_id != NO_TILE){

        Utils::CRect::RectangleSide collision_side = ship->rect.HasIntersection(tile_coll);

        printf("%d - tile_x: %d  tile_y: %d\n",  collision_side, tile_x, tile_y);
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
