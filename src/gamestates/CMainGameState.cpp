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
    level_load(this->engine->getLoadedLevel(), "map/teste01.cbm");
    this->level = this->engine->getLoadedLevel();
    ship = spaceship_get_player(SHIP_P1);
    spaceship_start(ship, &camera);
    spaceship_set_default_flags(ship);
    //spaceship_start(&ship, &camera);
    spaceship_camera_init(engine->getRenderWindow()->getWindow()->getSize().x, engine->getRenderWindow()->getWindow()->getSize().y, &camera, ship);
}

void CMainGameState::Start()
{





}

void CMainGameState::Destroy()
{

}

void CMainGameState::Update(sf::Time elapsed)
{
    spaceship_update(elapsed, SHIP_P1);
    spaceship_scrolling_update(elapsed, this->engine->getRenderWindow()->getWindow(), ship, &camera, this->level->map_width ,this->level->map_height);
     return;
}

void CMainGameState::Draw()
{

    for (int y = 0; y < this->level->map_width; y++) {
        for (int x = 0; x < this->level->map_width; x++) {
            sf::RectangleShape shape;
            shape.setPosition( (x * TILE_SIZE) - camera.x,  (y  * TILE_SIZE) - camera.y);
            shape.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineColor(sf::Color::Blue);
            shape.setOutlineThickness(1);

            //shape.setTexture( tile )

            this->engine->getRenderWindow()->getWindow()->draw(shape);
        }

    }


    spaceship_draw(this->engine->getRenderWindow()->getWindow(), ship, &camera);

}





void CMainGameState::HandleInput(sf::Time elapsed)
{
    return;
}
