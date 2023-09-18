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

   editor_set_level(this->mainEngine->getLoadedLevel());

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

void CEditorState::WindowHandlerUpdate(ALLEGRO_EVENT *e)
{
    UNUSED(e);
}

