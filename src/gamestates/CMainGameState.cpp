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
    spaceship_start(&ship, &camera);
    spaceship_camera_init(engine->getRenderWindow()->getWindow()->getSize().x, engine->getRenderWindow()->getWindow()->getSize().y, &camera, &ship);
}

void CMainGameState::Start()
{





}

void CMainGameState::Destroy()
{

}

void CMainGameState::Update(sf::Time elapsed)
{
    LOG("%d", elapsed.asSeconds());
    spaceship_update(elapsed,0);
     return;
}

void CMainGameState::Draw()
{

    for (int y = 0; y < this->level->map_width; y++) {
        for (int x = 0; x < this->level->map_width; x++) {
            engine->getRenderWindow()->getWindow()->draw(tiles_get_by_id( this->level->map_layer[y][x].id));
        }

    }


    spaceship_draw(this->engine->getRenderWindow()->getWindow(), &ship, &camera);
    spaceship_scrolling_update(this->engine->getRenderWindow()->getWindow(), &ship, &camera, 22,72);
}





void CMainGameState::HandleInput(sf::Time elapsed)
{
    return;
}
