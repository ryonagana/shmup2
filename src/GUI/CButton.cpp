#include "GUI/CButton.h"
#include "mouse.h"

GUI::CButton::CButton(float x, float y, std::string font_name, ALLEGRO_COLOR textColor, ALLEGRO_COLOR bgColor) : text_color(textColor), background_color(bgColor)
{
    m_text.LoadFontTTF(font_name, 12);
    m_button.setSize(0,0,215,65);
    vector_Init(&this->position, x,y);
}

GUI::CButton::~CButton()
{

}

void GUI::CButton::handleEvent(ALLEGRO_EVENT *e)
{
    if(mouse_get()->lButton){
        if(buttonRect.HasIntersection( Utils::CRect(mouse_get()->x, mouse_get()->y, mouse_get()->x + 16, mouse_get()->y + 16)))
        {
            m_function();
        }
    }
}

void GUI::CButton::Draw()
{
    al_draw_filled_rectangle(buttonRect.getX(),buttonRect.getY(), buttonRect.Right(), buttonRect.Bottom(), background_color);
    m_text.DrawText(text_color, position.x, position.y, "Button Test");
}

void GUI::CButton::SetWidgetPos(float x, float y)
{
    position.x = x;
    position.y = y;
}

void GUI::CButton::setFunction(MenuFunction function)
{
    m_function = std::bind(function);
}
