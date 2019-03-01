#ifndef MENU_HEADER
#define MENU_HEADER

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <vector>
#include <allegro5/allegro.h>

typedef enum  {
    MENU_TYPE_NONE,
    MENU_TYPE_SIMPLE,
    MENU_TYPE_PAGE
}MENU_TYPE;

//typedef bool (*menuSelectCallback)(int id);

using menuSelectCallback = std::function<bool(int)>;

typedef struct MENU_ENTRY {
    //char menu[56];
    std::string menu;
    int id;
    MENU_TYPE type;
    float x1,x2,y1,y2;
    menuSelectCallback menu_callback;

    MENU_ENTRY(){
        menu[0] = {};
        type = MENU_TYPE_NONE;
        menu_callback = nullptr;
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
    }



}MENU_ENTRY;




typedef struct MENU {
     //MENU_ENTRY *entries;
    std::vector<MENU_ENTRY> entries;
    int menu_count;
     int entries_count;
     int menu_selected;
     float bg_x;
     float bg_y;

     ~MENU(){
        entries.clear();
     }


}MENU;








void menu_init(void);
void menu_create(MENU *menu, int size);
void menu_destroy(MENU *menu);

void menu_add_entry(MENU *menu, int id,  const char *entry_name, MENU_TYPE type, std::function<bool(int)> callback);
void menu_remove_entry(MENU *menu, int index);

void menu_update(MENU* menu, ALLEGRO_EVENT *e);
void menu_draw(MENU* menu);
void menu_input_update(MENU *menu, ALLEGRO_EVENT *e);

#endif
