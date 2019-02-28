#pragma once
#include "states/IGameState.h"


class CMainGame : public IGameState {


    // IGameState interface
public:
    CMainGame();
    ~CMainGame() override;
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(ALLEGRO_EVENT *e) override;
    virtual void Draw() override;
};
