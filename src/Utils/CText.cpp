#include "Utils/CText.h"





void Utils::CText::TextRender(ALLEGRO_COLOR color, float x, float y, const std::string &text)
{
    if(this->font == nullptr) return;

    ALLEGRO_USTR *str = al_ustr_new_from_buffer(text.c_str(), text.size());
    al_draw_ustr(this->font, color, x,y, 0,  str);
    al_ustr_free(str);
}

Utils::CText::CText()
{
    this->font = nullptr;

}


void Utils::CText::LoadFontTTF(const std::string &font,int size)
{
    if(font.empty() && this->font == nullptr){
        this->font = al_create_builtin_font();
        return;
    }

    this->font = al_load_ttf_font(font.c_str(), size, ALLEGRO_TTF_NO_KERNING);
    return;

}

void Utils::CText::LoadBitmapFont(const std::string &font)
{
    this->font = al_load_bitmap_font(font.c_str());
    return;
}

void Utils::CText::DrawText(ALLEGRO_COLOR color, float x, float y, const char *fmt, ...)
{
    char buffer[2048];
    va_list lst;
    va_start(lst, fmt);
    vsnprintf(buffer, 2048, fmt, lst);
    va_end(lst);
    TextRender(color,x,y, buffer);

}

void Utils::CText::DrawTextShadow(ALLEGRO_COLOR color, ALLEGRO_COLOR shadow, float x, float y, const char *fmt,...)
{
    char buffer[2048];
    va_list lst;
    va_start(lst, fmt);
    vsnprintf(buffer, 2048, fmt, lst);
    va_end(lst);
    TextRender(color,x,y, buffer);
    TextRender(shadow,x + 2, y + 4, buffer);
}
