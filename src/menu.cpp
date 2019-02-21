#include "menu.h"
#include "keyboard.h"
#include "mouse.h"
#include "text.h"
#include "window.h"
#include "shared.h"


static MENU_ENTRY* menu_find_empty_slot(MENU *menu, int *index);
static bool menu_option_clicked(MENU_ENTRY *entry);

static GAME_TEXT menu_text;

void menu_init(void){
    text_init(&menu_text, nullptr, 45);

}

void menu_create(MENU *menu, int size){
    if(menu == nullptr){
        menu =  new MENU;
    }

    menu->entries_count = 0;
    menu->menu_count = size;
    menu->entries = new (std::nothrow) MENU_ENTRY[size + 1];  //(MENU_ENTRY*) malloc(sizeof(MENU_ENTRY) * size + 1);
    menu->bg_x = window_get_width() / 2 - 50;
    menu->bg_y = (window_get_height() / 2);
    for(int i = 0; i < size;i++){
        strncpy(menu->entries[i].menu, "", 56);
        menu->entries[i].id = i;
        menu->entries[i].type = MENU_TYPE_NONE;
    }

    menu->menu_count = size;

}


void menu_destroy(MENU *menu){
    if(menu){
        free(menu->entries);
        free(menu);
        menu->entries = nullptr;
        menu = nullptr;
    }
}

void menu_add_entry(MENU *menu, int id,  const char *entry_name, MENU_TYPE type, menuSelectCallback callback){
    int index = 0;
    MENU_ENTRY *entry = menu_find_empty_slot(menu, &index);

    strncpy(entry->menu, entry_name,56);
    entry->id = id;
    entry->menu_callback = callback;
    entry->type = type;
    menu->entries_count++;

    return;

}

static MENU_ENTRY* menu_find_empty_slot(MENU *menu, int *index){
    int i = 0;

    while(i < menu->entries_count) i++;

    if(i == menu->menu_count) return  nullptr;
    *index = i;
    return &menu->entries[i];
}

/* actually it doesnt remove just reset data */

void menu_remove_entry(MENU *menu, int index){
     MENU_ENTRY *entry = &menu->entries[index];

     strncpy(entry->menu,"", 56);
     entry->menu_callback = nullptr;
     entry->type = MENU_TYPE_NONE;
}

void menu_update(MENU* menu){
    if(menu->menu_count <= 0 ) return;


    for(int i = 0; i < menu->entries_count;i++){

        if(mouse_get()->y > (i * 25) + (window_get_height()) / 2){
            if( mouse_get()->x >  window_get_width() / 2 + 50 ){
                    menu->bg_x =  window_get_width() / 2 - 50 ;
                    menu->bg_y =  (i * 25) + (window_get_height() / 2);

                    menu_option_clicked(&menu->entries[i]);



            }
        }



    }




}

void menu_input_update(ALLEGRO_EVENT *e){


    if( keyboard_pressed(ALLEGRO_KEY_UP)){

    }

    if( keyboard_pressed(ALLEGRO_KEY_DOWN)){

    }

    if( keyboard_pressed(ALLEGRO_KEY_ENTER)){

    }
}

void menu_draw(MENU* menu){

    for(int i = 0; i < menu->menu_count;i++){
        al_draw_filled_rectangle(menu->bg_x, menu->bg_y, menu->bg_x + 200, menu->bg_y + 15, al_map_rgb(255,0,0));

        al_draw_textf(menu_text.font, al_map_rgb(255,0,0), (window_get_width() / 2 + 50) + 2 , (i * 25) + (window_get_height() / 2), 0,"%s", menu->entries[i].menu);
        al_draw_textf(menu_text.font, al_map_rgb(255,255,255), window_get_width() / 2 + 50 , (i * 25) + (window_get_height() / 2),0 , "%s",  menu->entries[i].menu);

        //text_draw(&menu_text, al_map_rgb(255,255,255), 150, i * 25, "%s", menu->entries[i].id);
    }
}

static bool menu_option_clicked(MENU_ENTRY *entry){
    if(mouse_get()->lButton){
        if( entry->menu_callback != nullptr){
            if(entry->menu_callback()){
                printf("Callback menu cahamado com sucesso! ID: %d \n", entry->id);
                return true;
            }
        }
        return false;
    }
    return false;
}
