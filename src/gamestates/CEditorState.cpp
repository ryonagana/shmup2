#include "gamestates/CEditorState.h"
#include "mouse.h"
#include "keyboard.h"

CEditorState::CEditorState(CEngine *parent) : mainEngine(parent)
{


}



void CEditorState::Init()
{


}

void CEditorState::Start()
{
    if(this->mainEngine->getLoadedLevel() == nullptr){

    }
        editor_load_mem(this->mainEngine->getLoadedLevel());
}

void CEditorState::Destroy()
{
}

void CEditorState::Update(ALLEGRO_EVENT *e)
{
    editor_update(e);
}

void CEditorState::HandleInput(ALLEGRO_EVENT *e)
{


    editor_update_input(e);
}

void CEditorState::Draw()
{
    editor_draw();
}
