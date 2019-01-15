#include "editor.h"


static EDITOR *editor = NULL;
static bool opened_dialog = false;


static void editor_move_camera(float x, float y);
static void editor_camera_bounds(void);
static TILE *editor_tile_get(TILE *map[MAX_GRID_Y][MAX_GRID_X],  int x, int y);
static void editor_tile_put(TILE_ID id, int x, int y);
static void editor_tile_set_property(int x, int y, bool passable, bool block);

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

    editor->camera = (CAMERA_EDITOR*) malloc(sizeof(CAMERA_EDITOR));
    editor->camera->height = window_get_height();
    editor->camera->width = window_get_width();
    editor->camera->x = 0;
    editor->camera->y = 0;



}
bool editor_load(LEVEL *level){
    editor->level  =  level;
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


    if(keyboard_pressed(ALLEGRO_KEY_W)){
        editor_move_camera(0,-1);
    }

    if(keyboard_pressed(ALLEGRO_KEY_S)){
        editor_move_camera(0,1);
    }


    if(keyboard_pressed(ALLEGRO_KEY_A)){
        editor_move_camera(-1,0);
    }

    if(keyboard_pressed(ALLEGRO_KEY_D)){
        editor_move_camera(1,0);
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


    int world_x = editor->camera->x + mouse_get()->x;
    int world_y = editor->camera->y + mouse_get()->y;
    int tile_x = world_x / TILE_SIZE;
    int tile_y = world_y / TILE_SIZE;




    if(mouse_get()->lButton){
        TILE *t = editor_tile_get(editor->level->map_layer, tile_x, tile_y);
        printf("\nTILE: x: %d y: %d id: %d\n", tile_x, tile_y, t->id);
    }


    editor_map_to_coord();
    editor_camera_bounds();




}


void editor_map_to_coord(void){
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




    al_draw_rectangle(editor->level->map_width * TILE_SIZE, editor->level->map_height * TILE_SIZE, (editor->level->map_width * TILE_SIZE) - editor->camera->x, (editor->level->map_height* TILE_SIZE) - editor->camera->y, al_map_rgb(0,255,0),2.0);


    for(int y = 0; y < editor->level->map_height; y++){
         for(int x = 0; x < editor->level->map_width; x++){
             al_draw_bitmap( tiles_get_by_id(editor->level->map_layer[y][x].id ), (TILE_SIZE * x) - editor->camera->x, (TILE_SIZE * y) - editor->camera->y,0);
         }
    }

        al_draw_rectangle(editor->editor_rect.x1,editor->editor_rect.y1,editor->editor_rect.x2,editor->editor_rect.y2,al_map_rgb(255,211,0),1.0);

}


void editor_destroy(void){
    if(editor->camera) free(editor->camera);
    editor->camera = NULL;

    if(editor) free(editor);
    editor = NULL;


}


static void editor_move_camera(float x, float y){
    editor->camera->x +=  TILE_SIZE * x;
    editor->camera->y +=  TILE_SIZE * y;

    if(editor->camera->x < 0) editor->camera->x = 0;
    if(editor->camera->y < 0) editor->camera->y = 0;

}

static void editor_camera_bounds(void){




    if(editor->camera->x < 0)  editor->camera->x = 0;

    if(editor->camera->x > editor->level->map_width * TILE_SIZE){
        editor->camera->x =  editor->level->map_width * TILE_SIZE ;
    }

     if(editor->camera->y < 0)  editor->camera->y = 0;

     if(editor->camera->y > editor->level->map_height * TILE_SIZE){
         editor->camera->y =  editor->level->map_height  * TILE_SIZE ;
     }


}

static TILE *editor_tile_get(TILE *map[MAX_GRID_Y][MAX_GRID_X],  int x, int y){
    return *(&map[y][x]);
}
