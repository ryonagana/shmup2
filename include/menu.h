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
    MENU_TYPE_PAGE,
    MENU_TYPE_OPTIONS
}MENU_TYPE;


typedef bool (*menuSelectCallback)(void);

typedef struct MENU_ENTRY {
    char menu[56];
    int id;
    MENU_TYPE type;
    menuSelectCallback menu_callback;

}MENU_ENTRY;


typedef struct MENU {
     MENU_ENTRY *entries;
     int menu_count;
     int entries_count;
     int menu_selected;
     float bg_x;
     float bg_y;

}MENU;

void menu_init(void);
void menu_create(MENU *menu, int size);
void menu_destroy(MENU *menu);

void menu_add_entry(MENU *menu, int id,  const char *entry_name, MENU_TYPE type, menuSelectCallback callback);
void menu_remove_entry(MENU *menu, int index);

void menu_update(MENU* menu);
void menu_draw(MENU* menu);
void menu_input_update(ALLEGRO_EVENT *e);

#endif
