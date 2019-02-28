#pragma once
#include "states/IGameState.h"


class CMainGameState : public IGameState {


    // IGameState interface
public:
    CMainGameState();
    ~CMainGameState() override;
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(ALLEGRO_EVENT *e) override;
    virtual void UpdateInput(ALLEGRO_EVENT *e) override;
    virtual void Draw() override;


};
