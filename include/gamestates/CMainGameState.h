#pragma once
#include "states/IGameState.h"
#include "CEngine.h"

class CEngine;

class CMainGameState : public IGameState {

private:
    CEngine *engine;

    // IGameState interface
public:
    CMainGameState();
    CMainGameState(CEngine *parent = nullptr);
    ~CMainGameState() override;
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(ALLEGRO_EVENT *e) override;
    virtual void UpdateInput(ALLEGRO_EVENT *e) override;
    virtual void Draw() override;


};
