#ifndef TEXT_HEADER
#define TEXT_HEADER

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdarg.h>

typedef struct GAME_TEXT {
    ALLEGRO_FONT *font;
    int font_width;
    int font_size;

}GAME_TEXT;

void text_init(GAME_TEXT *text, const char *font_path,  int size);
void text_draw(GAME_TEXT *text, ALLEGRO_COLOR color, float x, float y,  const char *fmt,...);
void text_destroy(GAME_TEXT *text);

#endif
