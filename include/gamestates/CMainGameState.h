#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include "states/IGameState.h"
#include "CEngine.h"
#include "spaceship.h"
#include "render.h"


class CEngine;

class CMainGameState : public IGameState {

private:
    CEngine *engine;
    SPACESHIP *ship;
    CAMERA    ship_camera;
    LEVEL *level;

    ALLEGRO_BITMAP *ship_bmp;

    bool collisionHighlight; // for debug purposes only;


    // IGameState interface
public:
    CMainGameState();
    CMainGameState(CEngine *parent = nullptr);
    ~CMainGameState() override;
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(ALLEGRO_EVENT *e) override;
    virtual void HandleInput(ALLEGRO_EVENT *e) override;
    virtual void Draw() override;


};
