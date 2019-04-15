#pragma once
#include <iostream>
#include "states/IGameState.h"
//#include "editor.h"
#include "CEngine.h"
class CEditorState : public IGameState {
private:
    CEngine *mainEngine;

    // IGameState interface
public:
    CEditorState(CEngine *parent);
    virtual void Init() override;
    virtual void Start() override;
    virtual void Destroy() override;
    virtual void Update(sf::Time elapsed) override;
    virtual void HandleInput(sf::Time elapsed) override;
    virtual void Draw() override;
};
