#include "editor.h"


static EDITOR *editor = NULL;
static bool opened_dialog = false;

void editor_init(void){
    editor = (EDITOR*) malloc(sizeof (EDITOR));
    if(!editor) CRITICAL("EDITOR NOT LOADED!");
    editor->level = NULL;
    editor->state = EDITOR_STATE_EDIT;
    editor->selected_tile = NO_TILE;
    editor->old_selected_tile = NO_TILE;

    editor->editor_rect.x1 = 0;
    editor->editor_rect.y1 = 0;
    editor->editor_rect.x2 = 0;
    editor->editor_rect.y2 = 0;

    editor->camera = (CAMERA*) malloc(sizeof(CAMERA));
    editor->camera->height = window_get_height();
    editor->camera->width = window_get_width();
    editor->camera->x = mouse_get()->x;
    editor->camera->y = mouse_get()->y;

}
bool editor_load(LEVEL *level, CAMERA *cam){
    editor->level  =  level;

    if(cam != NULL) editor->camera = cam;
    return editor->level == NULL ? false : true;
}

void editor_update_keyboard(ALLEGRO_EVENT *e)
{
    if(keyboard_pressed(ALLEGRO_KEY_LCTRL) && editor->state != EDITOR_STATE_SAVE ){
        if(keyboard_pressed(ALLEGRO_KEY_F1) && editor->state != EDITOR_STATE_SAVE){
            editor->state = EDITOR_STATE_SAVE;
            opened_dialog = true;
        }
    }

    if(keyboard_pressed(ALLEGRO_KEY_LCTRL) && editor->state != EDITOR_STATE_SAVE ){
        if(keyboard_pressed(ALLEGRO_KEY_S) && editor->state != EDITOR_STATE_SAVE){
            editor->state = EDITOR_STATE_LOAD;
        }
    }
}

void editor_update(ALLEGRO_EVENT *e)
{
    if(editor->state == EDITOR_STATE_SAVE && opened_dialog){
        opened_dialog = false;

        editor->state = EDITOR_STATE_INIT;
        if(!level_save(get_window_display(), editor->level,"mapa01",true)){
            return;
        }

    }

        //TILE *t = level_get_tile(editor->level->map_layer, x, y);

        int tilex = 0;
        int tiley = 0;

        for(unsigned int y = 0; y < editor->level->map_height;++y){
            for(unsigned int x = 0; x < editor->level->map_width;++x){
                tiley = (mouse_get()->y / TILE_SIZE);
                tilex = (mouse_get()->x / TILE_SIZE);

            }
        }

        printf("\nX: %d Y: %d\n", tilex, tiley);

        float x1 = (mouse_get()->x / TILE_SIZE) * TILE_SIZE;
        float x2 = TILE_SIZE * (mouse_get()->x / TILE_SIZE) + TILE_SIZE;
        float y1 = (mouse_get()->y / TILE_SIZE) * TILE_SIZE;
        float y2 = TILE_SIZE * (mouse_get()->y / TILE_SIZE) + TILE_SIZE;
        editor->editor_rect.x1 = x1;
        editor->editor_rect.y1 = y1;
        editor->editor_rect.x2 = x2;
        editor->editor_rect.y2 = y2;



}

void editor_render(void)
{

    al_draw_rectangle(editor->editor_rect.x1,editor->editor_rect.y1,editor->editor_rect.x2,editor->editor_rect.y2,al_map_rgb(255,211,0),1.0);


}
