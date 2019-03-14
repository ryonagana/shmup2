#include "GUI/CButtonRect.h"
#include "shared.h"
#include "mouse.h"

bool GUI::CButtonRect::onMouseOver(ALLEGRO_EVENT *e) const
{
    UNUSED_PARAM(e);
    CRect mouseRect(mouse_get()->x, mouse_get()->y, mouse_get()->x + 16, mouse_get()->y + 16);

    if( this->HasIntersection(mouseRect)){
        return true;
    }

    return false;
}

bool GUI::CButtonRect::onClick(ALLEGRO_EVENT *e)
{
    if(onMouseOver(e)){
        if(mouse_get()->lButton){
            return true;
        }
    }

    return false;
}
