#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include "Utils/CRect.h"
#include "Utils/CText.h"
#include "GUI/CButtonRect.h"
namespace GUI {
    class CWidget {
    private:
    public:
        CWidget();
        virtual ~CWidget() {}
        virtual void handleEvent(ALLEGRO_EVENT *e) = 0;
        virtual void Draw() = 0;
        virtual void SetWidgetPos(float x, float y) = 0;

        GUI::CButtonRect buttonRect;

        class WidgetText : public  Utils::CText{
        public:
            WidgetText();
        };

    };
}
