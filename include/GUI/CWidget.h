#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include "Utils/CRect.h"
#include "text.h"

namespace GUI {
    class CWidget {
    private:

       GAME_TEXT *text;
    public:
        virtual ~CWidget() = 0;
        virtual void handleEvent(ALLEGRO_EVENT *e) = 0;
        virtual void Draw() = 0;
        virtual void SetWidgetPos(float x, float y) = 0;


        class ButtonRect : public Utils::CRect {
            bool onMouseOver(ALLEGRO_EVENT *e);
            bool onClick(ALLEGRO_EVENT *e);
        };
    };
}
