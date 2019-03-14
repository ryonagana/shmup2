#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

namespace Utils
{

    class CText {
    private:
        ALLEGRO_FONT *font;

        void TextRender(ALLEGRO_COLOR color, float x, float y, const std::string &text);

    public:
        CText();

        void LoadFontTTF(const std::string &font, int size);
        void LoadBitmapFont(const std::string &font);

        void DrawText(ALLEGRO_COLOR color,   float x, float y, const char *fmt,...);
        void DrawTextShadow(ALLEGRO_COLOR color, ALLEGRO_COLOR shadow, float x, float y, const char *fmt,...);


    };

}
