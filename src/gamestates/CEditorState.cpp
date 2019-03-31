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

void CEditorState::Update(sf::Time elapsed)
{
    //editor_update(e);
}

void CEditorState::HandleInput(sf::Time elapsed)
{


   // editor_update_input(elapsed);
}

void CEditorState::Draw()
{
    editor_draw();
}
