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
    spaceship_draw(this->engine->getRenderWindow()->getWindow(), &ship, &camera);
    spaceship_scrolling_update(this->engine->getRenderWindow()->getWindow(), &ship, &camera, 22,72);
}





void CMainGameState::HandleInput(sf::Time elapsed)
{
    return;
}
