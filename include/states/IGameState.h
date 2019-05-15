#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <memory>
#include "states/NonCopyable.h"
#include "states/NonMovable.h"

enum class GameStateID : int {
    Menu = 1,
    MainGame,
    Editor
};

class IGameState : public NonCopyable, public NonMovable {
protected:



public:



    int id;
    GameStateID stateId;
    bool active;
    std::string name; // name of this event..
    IGameState(){}
    virtual ~IGameState() {}

    // pure functions states functions
    virtual void Init() = 0;  // to init variables
    virtual void Start() = 0; // to start them
    virtual void Destroy() = 0; // destroy

    /* this pure virtual function os for every state must have this draw function */
    virtual void Update(ALLEGRO_EVENT *e) = 0;  //must  be put inside  ALLEGRO_EVENT_TIMER everything that needs be  updated with fixed time
    virtual void HandleInput(ALLEGRO_EVENT *e) = 0;  //this must be outside ALLEGRO_EVENT_TIMER is related to keyboard, mouse, joypad
    virtual void Draw() = 0; // this function must be put inside  when things is being Drawn


};


