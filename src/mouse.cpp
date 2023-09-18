#include "mouse.h"
#include "window.h"
#include "path.h"
#include "shared.h"

static mouse_t *mouse_input = nullptr;

static ALLEGRO_BITMAP *mouse_cursor = nullptr;
static ALLEGRO_MOUSE_CURSOR *a5_editor_mouse = nullptr;

void mouse_init(void){
    if(mouse_input == nullptr){
        mouse_input = new mouse_t;//(MOUSE*) malloc(sizeof(MOUSE));
    }

    mouse_input->lButton = false;
    mouse_input->rButton = false;
    mouse_input->x = 0;
    mouse_input->y = 0;
    mouse_input->z = 0.0;

    char *path = get_file_path("tile", "mouse_cursor.png");

    mouse_cursor = al_load_bitmap(path);

    if(mouse_cursor == nullptr){
        mouse_cursor = al_create_bitmap(16,16);
        al_set_target_bitmap(mouse_cursor);
        al_draw_filled_rectangle(0,16,16,0, al_map_rgb(255,0,255));
        al_set_target_backbuffer(GameWindow::getInstance().getDisplay());
    }

    LOG("Mouse Cursor: %s successfully loaded!", path);


    a5_editor_mouse = al_create_mouse_cursor(mouse_cursor, 0, 0);
    al_set_mouse_cursor(GameWindow::getInstance().getDisplay(), a5_editor_mouse);

    LOG("Mouse Cursor SET Sucess!");



}


void mouse_destroy(void){
    if(mouse_input) delete[] mouse_input;
    mouse_input = nullptr;

    if(a5_editor_mouse) al_destroy_mouse_cursor(a5_editor_mouse);
    a5_editor_mouse = nullptr;

}


mouse_t *mouse_get(void){
    if(!mouse_input) return nullptr;
    return mouse_input;
}

void mouse_update(ALLEGRO_EVENT *e){
    if(e->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(e->mouse.button & 1){
            mouse_input->lButton = true;
        }

     if(e->mouse.button    & 2){
            mouse_input->rButton = true;
        }
    }

    if(e->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        if(e->mouse.button & 1){
            mouse_input->lButton = false;
        }

     if(e->mouse.button    & 2){
            mouse_input->rButton = false;
        }
    }

    if(e->type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_input->x = e->mouse.x;
        mouse_input->y = e->mouse.y;
        mouse_input->z = e->mouse.dz;
    }


}

void  mouse_set(int x, int y){
    al_set_mouse_xy(GameWindow::getInstance().getDisplay(), x,y);
}
