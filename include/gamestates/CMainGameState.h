#pragma once
#include "states/IGameState.h"
#include "CEngine.h"
#include "spaceship.h"
//#include "render.h"


class CEngine;

class CMainGameState : public IGameState {

private:
    CEngine *engine;
    LEVEL *level;
    SPACESHIP *ship;
    CAMERA    camera;

    // IGameState interface
public:
    CMainGameState();
    CMainGameState(CEngine *parent = nullptr);
    ~CMainGameState() override;
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(sf::Time elapsed) override;
    virtual void HandleInput(sf::Time elapsed) override;
    virtual void Draw() override;


};
