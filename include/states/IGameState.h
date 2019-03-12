#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <memory>
#include "NonCopyable.h"

enum class GAMESTATE_ID : uint32_t {
    GAMESTATE_MENU,
    GAMESTATE_GAME,
    GAMESTATE_SELECT_MAP,
    GAMESTATE_SELECT_MAP_EDITOR,
    GAMESTATE_EDITOR
};

class IGameState  {
protected:



public:
    int id;
    bool active;
    std::string name; // name of this event..

    virtual ~IGameState() {}

    // pure functions states functions
    virtual void Init() = 0;  // to init variables
    virtual void Start() = 0; // to start them
    virtual void Destroy() = 0; // destroy

    /* this pure virtual function os for every state must have this draw function */
    virtual void Update(ALLEGRO_EVENT *e) = 0;  //must  be put inside  ALLEGRO_EVENT_TIMER
    virtual void HandleInput(ALLEGRO_EVENT *e) = 0;  //this must be outside ALLEGRO_EVENT_TIMER is related to keyboard, mouse, joypad
    virtual void Draw() = 0; // mst be put when things is being Draw


};

using GameState = std::unique_ptr<IGameState>;
