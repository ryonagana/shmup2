#ifndef MENU_HEADER
#define MENU_HEADER

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <allegro5/allegro.h>

typedef enum  {
    MENU_TYPE_NONE,
    MENU_TYPE_SIMPLE,
    MENU_TYPE_PAGE
}MENU_TYPE;


struct MENU;





typedef bool (*menuSelectCallback)(MENU *menu, int id);

typedef struct MENU_ENTRY {
    char menu[56];
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
     MENU_ENTRY *entries;
     int menu_count;
     int entries_count;
     int menu_selected;
     float bg_x;
     float bg_y;

     ~MENU(){
         if(entries) delete[] entries;
         entries = nullptr;
     }


}MENU;

void menu_init(void);
void menu_create(MENU *menu, int size);
void menu_destroy(MENU *menu);

void menu_add_entry(MENU *menu, int id,  const char *entry_name, MENU_TYPE type, menuSelectCallback callback);
void menu_remove_entry(MENU *menu, int index);

void menu_update(MENU* menu, ALLEGRO_EVENT *e);
void menu_draw(MENU* menu);
void menu_input_update(MENU *menu, ALLEGRO_EVENT *e);

#endif
