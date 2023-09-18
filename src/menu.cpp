#include "menu.h"
#include "keyboard.h"
#include "mouse.h"
#include "text.h"
#include "window.h"
#include "shared.h"


static bool menu_option_clicked(MENU *menu, int index);


static bool menu_mouse_on_entry(float x1, float y1, float x2, float y2);

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
    menu->entries = std::vector<MENU_ENTRY>(); //new (std::nothrow) MENU_ENTRY[size + 1];  //(MENU_ENTRY*) malloc(sizeof(MENU_ENTRY) * size + 1);
    menu->entries.reserve(static_cast<size_t>(size));
    menu->bg_x = GameWindow::getInstance().getWidth() / 2;
    menu->bg_y = (GameWindow::getInstance().getHeight() / 2);

    int i = 0;

    for(auto e :  menu->entries){

        e.menu = "";
        e.id = i;
        e.type = MENU_TYPE_NONE;
        ++i;
    }



    menu->menu_count = size;

}


void menu_destroy(MENU *menu){
    if(menu){
        menu->entries.clear();
        delete[] menu;
        menu = nullptr;
    }
}

void menu_add_entry(MENU *menu, int id,  const char *entry_name, MENU_TYPE type, std::function<bool(int)> callback){

    MENU_ENTRY *entry = new MENU_ENTRY;

    entry->id = id;
    entry->menu = entry_name;
    entry->type = type;
    entry->menu_callback = nullptr;
    if(callback != nullptr) {
        entry->menu_callback =  std::bind(callback, id);
    }
    menu->entries.push_back(*entry);
    menu->entries_count = static_cast<int>(menu->entries.size());

    //menu->entries.push_back()
    /*
    int index = 0;
    MENU_ENTRY *entry = menu_find_empty_slot(menu, &index);

    entry->menu = entry_name;
    //strncpy(entry->menu, entry_name,56);
    entry->id = id;
    entry->menu_callback = callback;
    entry->type = type;
    entry->x1 =  window_get_width() / 2 - 50;
    entry->y1 = (25 * menu->entries_count) + window_get_height() / 2;
    entry->x2 = 125;
    entry->y2 = (25 * menu->entries_count) + 5;


    menu->entries_count++;
    */

    return;

}



/* actually it doesnt remove just reset data */

void menu_remove_entry(MENU *menu, int index){

    menu->entries.erase(menu->entries.begin()  + index);

}

void menu_update(MENU* menu, ALLEGRO_EVENT *e){
    static int click_counter = 0;

    int sw,sh;

    sw = GameWindow::getInstance().getWidth();
    sh = GameWindow::getInstance().getHeight();

    if(menu->menu_count <= 0 ) return;
    if(menu->entries_count <= 0) return ;

    for(int i = 0; i < menu->entries_count;i++){

        if(mouse_get()->y > (i * 25) + sh / 2){
            if( mouse_get()->x >  sw / 2 + 50 ){
                    menu->bg_x =  sw / 2;
                    menu->bg_y =  (25 * i) +  sh / 2;

                    if(!mouse_get()->lButton && menu_mouse_on_entry(menu->bg_x, menu->bg_y, menu->bg_x + 200, menu->bg_y + 15 )){
                            menu->menu_selected = i;
                    }
            }
        }
    }


    if(mouse_get()->lButton){
        // jst for slow down the click
        // was very fast you cant select the map cause it clicks  multiple times in a short time
        click_counter++;


        if(click_counter >= 5){
            menu_option_clicked(menu, menu->menu_selected);
            click_counter = 0;
        }

    }

    menu_input_update(menu, e);
}

void menu_input_update(MENU *menu, ALLEGRO_EVENT *e){

    UNUSED(e);

    if(menu->menu_selected <= 0)  menu->menu_selected = 0;
    if(menu->menu_selected > menu->entries_count - 1) menu->menu_selected = menu->entries_count - 1;


    if( keyboard_pressed(ALLEGRO_KEY_UP)){
        menu->bg_y =  (25 * menu->menu_selected) +  GameWindow::getInstance().getHeight() / 2;
        menu->menu_selected--;
    }

    if( keyboard_pressed(ALLEGRO_KEY_DOWN)){
        menu->bg_y =  (25 * menu->menu_selected) +  GameWindow::getInstance().getHeight() / 2;
        menu->menu_selected++;
    }

    if( keyboard_pressed(ALLEGRO_KEY_ENTER)){
        menu_option_clicked(menu, menu->menu_selected);
    }
}

void menu_draw(MENU* menu){
    int i = 0;

    int sw = GameWindow::getInstance().getWidth();
    int sh = GameWindow::getInstance().getHeight();

    if(menu->entries_count <= 0 ) {
        al_draw_textf(menu_text.font, al_map_rgb(255,0,0), (sw / 2 + 50) + 2 , (1 * 25) + (sh / 2), 0,"No Menu Option.");
        return;
    }

    al_draw_filled_rectangle(menu->bg_x, menu->bg_y, menu->bg_x + 200, menu->bg_y + 15, al_map_rgb(255,0,0));

    for(auto e : menu->entries){

        al_draw_textf(menu_text.font, al_map_rgb(255,0,0), (sw / 2 + 50) + 2 , (i * 25) + (sh / 2), 0,"%s", e.menu.c_str());
        al_draw_textf(menu_text.font, al_map_rgb(255,255,255), sw / 2 + 50 , (i * 25) + (sh / 2),0 , "%s",  e.menu.c_str());
        i++;
    }

    return;
}

static bool menu_option_clicked(MENU *menu, int index){
   MENU_ENTRY *entry = nullptr;

   entry = &menu->entries[static_cast<size_t>(index)];

   if(entry->menu_callback == nullptr){
       WARN("Menu Option [ %s ] has no action callback -- ignoring", entry->menu.c_str());
       return false;
    }

   if(!entry->menu_callback(index))
   {
       return false;
   }

   return true;

}

static bool menu_mouse_on_entry(float x1, float y1, float x2, float y2){
    if(x1 < x2 && x2 > x1 && y1 > y1 && y2 < y1)
    {
        return false;
    }

    return true;
}
