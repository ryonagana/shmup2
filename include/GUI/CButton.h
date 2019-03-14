#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <allegro5/allegro_primitives.h>
#include "GUI/CWidget.h"
#include "GUI/CButtonRect.h"
#include "Utils/CText.h"
#include "vector2.h"

using MenuFunction = std::function<void(void)>;

namespace GUI {
    class CButton : public GUI::CWidget
    {

    public:
        CButton(float x, float y, std::string font_name = "" , ALLEGRO_COLOR textColor = al_map_rgb(255,255,255), ALLEGRO_COLOR bgColor = al_map_rgb(255,0,0));
        ~CButton() override;
        virtual void handleEvent(ALLEGRO_EVENT *e) override;
        virtual void Draw() override;
        virtual void SetWidgetPos(float x, float y) override;
        void setFunction(MenuFunction function);

    private:
        ALLEGRO_COLOR text_color;
        ALLEGRO_COLOR background_color;

        VECTOR2 position;
        CButtonRect m_button;
        Utils::CText m_text;
        MenuFunction m_function = [](){ }; // to avoid init as nullptr it might crash if the function doesnt exists, this way only thing can happen  its  just nothing happens
    };


}


inline std::unique_ptr<GUI::CButton> makeButton(float x, float y, std::string font_name = "" , ALLEGRO_COLOR textColor = al_map_rgb(255,255,255), ALLEGRO_COLOR bgColor = al_map_rgb(255,0,0)) { return std::make_unique<GUI::CButton>(x,y,font_name,textColor,bgColor); }
