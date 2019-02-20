#include "text.h"

void text_init(GAME_TEXT *text, const char *font_path, int size){

    if(font_path == nullptr) text->font = al_create_builtin_font();
    else text->font = al_load_ttf_font(font_path, size, 0);

    text->font_width = 0;
    text->font_size = size;

}

void text_draw(GAME_TEXT *text, ALLEGRO_COLOR color, float x, float y,  const char *fmt,...){

    if(!text) return;

    char buffer[2048];
    ALLEGRO_USTR *str = nullptr;

    va_list lst;
    va_start(lst, fmt);
    vsnprintf(buffer, 2048, fmt, lst);
    va_end(lst);

    str = al_ustr_new_from_buffer(buffer, strlen(buffer));

   al_draw_ustr(text->font, color, x,y, ALLEGRO_ALIGN_LEFT,str);

   al_ustr_free(str);

}

void text_destroy(GAME_TEXT *text){
    if(text) al_destroy_font(text->font);

    free(text);
    text = nullptr;
}
