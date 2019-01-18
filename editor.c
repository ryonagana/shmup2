#include "editor.h"
#include "tiles.h"

static EDITOR *editor = NULL;
static bool opened_dialog = false;
static ALLEGRO_BITMAP *editor_cursor = NULL;


static ALLEGRO_BITMAP *canvas_screen = NULL;
static ALLEGRO_BITMAP *tools_screen  = NULL;
static ALLEGRO_FONT *editor_default_font = NULL;

static char state_text[65];

static void editor_move_camera(float x, float y);
static void editor_clear_screen(ALLEGRO_BITMAP* bmp, ALLEGRO_COLOR col);
static void editor_camera_bounds(void);
static TILE *editor_tile_get(TILE map[MAX_GRID_Y][MAX_GRID_X], int tile_x, int tile_y);
static void editor_tile_put(TILE *map, TILE_ID id);




static void editor_layer_to_str(EDITOR_LAYER_STATE state);

void editor_init(void){
    editor = (EDITOR*) malloc(sizeof (EDITOR));
    if(!editor) CRITICAL("EDITOR NOT LOADED!");
    editor->level = NULL;
    editor->state = EDITOR_STATE_EDIT;
    editor->selected_tile = TILE_GROUND01_F;
    editor->old_selected_tile = TILE_GROUND01_F;

    editor->editor_rect.x1 = 0;
    editor->editor_rect.y1 = 0;
    editor->editor_rect.x2 = 0;
    editor->editor_rect.y2 = 0;

    editor->camera = (CAMERA_EDITOR*) malloc(sizeof(CAMERA_EDITOR));
    editor->camera->height = window_get_height();
    editor->camera->width = window_get_width();
    editor->camera->x = 0;
    editor->camera->y = 0;

    editor->layer = EDITOR_LAYER_MAP;

    char *path = get_file_path("tile", "editor_cursor.png");

    editor_cursor = al_load_bitmap(path);

    if(editor_cursor == NULL){
        editor_cursor = al_create_bitmap(TILE_SIZE,TILE_SIZE);
        al_set_target_bitmap(editor_cursor);
        al_draw_rectangle(0,0,32,32,al_map_rgb(255,0,0),1.0);
        al_set_target_backbuffer(get_window_display());
    }


    canvas_screen = al_create_bitmap( CANVAS_GRID_W * TILE_SIZE , CANVAS_GRID_H * TILE_SIZE );
    tools_screen = al_create_bitmap(  5 * TILE_SIZE,  CANVAS_GRID_H * TILE_SIZE );

    editor_clear_screen(canvas_screen, al_map_rgb(0,0,0));
    editor_clear_screen(tools_screen, al_map_rgb(0,127,0));

    editor_default_font = al_create_builtin_font();

    memset(editor->map_path, 0, sizeof (char) * 4096);

    editor->dirty = false;
    if(path)free(path);



}

LEVEL* editor_load_path(const char *filename){

    LEVEL *level = NULL;

    level = (LEVEL*) malloc(sizeof(LEVEL));

    level_load(get_window_display(), level, filename, false);
    char *full_path = get_file_path("map", filename);
    strncpy(editor->map_path, full_path, strlen(full_path));

    editor->level = level;

    if(full_path) free(full_path);




    return level;

}

bool editor_load_mem(LEVEL *level){

    char *layer_name = NULL;

    editor->level  =  level;
    editor->layer  = EDITOR_LAYER_MAP;

    al_set_window_title(get_window_display(), "CB EDITOR - noname.cbm");

    editor_layer_to_str(editor->layer);
    if(layer_name) free(layer_name);

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

    if(keyboard_pressed(ALLEGRO_KEY_LCTRL) && editor->state != EDITOR_STATE_LOAD && !opened_dialog ){
        if(keyboard_pressed(ALLEGRO_KEY_F2) && editor->state != EDITOR_STATE_LOAD && !opened_dialog){
            editor->state = EDITOR_STATE_LOAD;
            opened_dialog = true;
            char map_loaded_name[2048];

            if(level_load(get_window_display(), editor->level, map_loaded_name, false)){
                printf("MAP LOADED %s", map_loaded_name);

            }
            opened_dialog = false;

            editor->state = EDITOR_STATE_EDIT;

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




    if(keyboard_pressed(ALLEGRO_KEY_1)){
        if(editor->layer == EDITOR_LAYER_BG) return;

        editor->layer = EDITOR_LAYER_BG;
    }

    if(keyboard_pressed(ALLEGRO_KEY_2)){
        if(editor->layer == EDITOR_LAYER_MAP) return;

        editor->layer = EDITOR_LAYER_MAP;
    }

    if(keyboard_pressed(ALLEGRO_KEY_3)){
        if(editor->layer == EDITOR_LAYER_OBJ) return;

        editor->layer = EDITOR_LAYER_OBJ;

    }

    if(keyboard_pressed(ALLEGRO_KEY_4)){
        if(editor->layer == EDITOR_LAYER_ALL) return;

        editor->layer = EDITOR_LAYER_ALL;

    }


     editor_layer_to_str(editor->layer);


}

void editor_update(ALLEGRO_EVENT *e)
{



    if(editor->state == EDITOR_STATE_SAVE){
        opened_dialog = false;
        editor->state = EDITOR_STATE_EDIT;
        if(!level_save(get_window_display(), editor->level,"mapa01",true)){
            return;
        }
        return;
    }



    if( (mouse_get()->x / TILE_SIZE) >  CANVAS_GRID_W - 1 ){
        return;
    }

    if( (mouse_get()->y / TILE_SIZE) >  CANVAS_GRID_H - 1){
        return;
    }



    int world_x = editor->camera->x + mouse_get()->x;
    int world_y = editor->camera->y + mouse_get()->y;
    int tile_x = world_x / TILE_SIZE;
    int tile_y = world_y / TILE_SIZE;


    if(mouse_get()->rButton && editor->state != EDITOR_STATE_NO_EDIT){

        TILE *t = NULL;
        editor->dirty = true;

        switch(editor->layer){
            case EDITOR_LAYER_BG:
                t = editor_tile_get(editor->level->bg_layer  , tile_x, tile_y);
            break;

            case EDITOR_LAYER_MAP:
                t = editor_tile_get(editor->level->map_layer  , tile_x, tile_y);
            break;
            case EDITOR_LAYER_OBJ:
                t = editor_tile_get(editor->level->obj_layer  , tile_x, tile_y);
            break;

            case EDITOR_LAYER_ALL:
                t = NULL;
                editor->state = EDITOR_STATE_NO_EDIT;
            break;
        }

        if(t){
            editor_tile_put(t, NO_TILE);
            printf("\nTILE: x: %d y: %d\n", tile_x, tile_y);
            printf("\nTILE ERASED!\n");
        }

    }


    if(mouse_get()->lButton && editor->state != EDITOR_STATE_NO_EDIT){


        TILE *t = NULL;

        switch(editor->layer){
            case EDITOR_LAYER_BG:
                t = editor_tile_get(editor->level->bg_layer  , tile_x, tile_y);
            break;

            case EDITOR_LAYER_MAP:
                t = editor_tile_get(editor->level->map_layer  , tile_x, tile_y);
            break;
            case EDITOR_LAYER_OBJ:
                t = editor_tile_get(editor->level->obj_layer  , tile_x, tile_y);
            break;

            case EDITOR_LAYER_ALL:
                t = NULL;
                editor->state = EDITOR_STATE_NO_EDIT;
            break;
        }


        if(t){

            if(t->id == editor->selected_tile) return;

            editor_tile_put(t, editor->selected_tile);
            printf("\nTILE: x: %d y: %d\n", tile_x, tile_y);
            printf("\nTILE ID: %d BLOCK: %d PASSABLE: %d\n", t->id, t->block, t->passable);
        }


    }


    editor_map_to_coord();
    editor_camera_bounds();




}


void editor_map_to_coord(void)
{
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





    //al_draw_rectangle(editor->level->map_width * TILE_SIZE, editor->level->map_height * TILE_SIZE, (editor->level->map_width * TILE_SIZE) - editor->camera->x, (editor->level->map_height* TILE_SIZE) - editor->camera->y, al_map_rgb(0,255,0),2.0);

    al_set_target_bitmap(canvas_screen);

    for(int y = 0; y < MAX_GRID_Y; y++){
         for(int x = 0; x < MAX_GRID_X; x++){

            if( x < editor->level->map_width && y < editor->level->map_height){
                al_draw_bitmap( tiles_get_by_id(editor->level->map_layer[y][x].id ), (TILE_SIZE * x) - editor->camera->x, (TILE_SIZE * y) - editor->camera->y,0);
            }

            al_draw_rectangle(x * TILE_SIZE, y * TILE_SIZE, (x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE, al_map_rgb(0,0,153),1.0);

         }
    }

    al_set_target_backbuffer(get_window_display());


   //al_draw_bitmap_region(canvas_screen,editor->camera->x,editor->camera->y, al_get_bitmap_width(canvas_screen), al_get_bitmap_height(canvas_screen),editor->camera->x,editor->camera->y,0);
   al_draw_bitmap(canvas_screen,0,20,0);
   al_draw_bitmap(tools_screen, (CANVAS_GRID_W * TILE_SIZE), EDITOR_TOP_SPACER,0);


   al_draw_filled_rectangle(0,EDITOR_TOP_SPACER, al_get_display_width(get_window_display()), 0, al_map_rgb(0,0,0));
   al_draw_textf(editor_default_font, al_map_rgb(255,0,0), 0,5, ALLEGRO_ALIGN_LEFT, "Layer: %s", state_text);

   al_draw_bitmap(editor_cursor, editor->editor_rect.x1, editor->editor_rect.y1 + EDITOR_TOP_SPACER, 0);


}


void editor_destroy(void)
{
    if(editor->camera) free(editor->camera);
    editor->camera = NULL;

    if(editor->level) free(editor->level);
    editor->level;

    if(editor) free(editor);
    editor = NULL;

    if(editor_cursor) al_destroy_bitmap(editor_cursor);
    if(canvas_screen) al_destroy_bitmap(canvas_screen);
    if(tools_screen) al_destroy_bitmap(tools_screen);

    if(editor_default_font) al_destroy_font(editor_default_font);


}


static void editor_move_camera(float x, float y){
    editor->camera->x +=  TILE_SIZE * x;
    editor->camera->y +=  TILE_SIZE * y;

    if(editor->camera->x < 0) editor->camera->x = 0;
    if(editor->camera->y < 0) editor->camera->y = 0;

}

static void editor_camera_bounds(void)
{



    int canvas_width  = al_get_bitmap_width(canvas_screen);
    int canvas_height = al_get_bitmap_height(canvas_screen);

    if(editor->camera->x < 0)  editor->camera->x = 0;

    if(editor->camera->x > (editor->level->map_width * TILE_SIZE) - canvas_width  ){
        editor->camera->x =  (editor->level->map_width * TILE_SIZE) - canvas_width ;
    }

     if(editor->camera->y < 0)  editor->camera->y = 0;

     if(editor->camera->y > (editor->level->map_height * TILE_SIZE) - canvas_height){
         editor->camera->y =  (editor->level->map_height  * TILE_SIZE) - canvas_height ;
     }





}

static TILE* editor_tile_get(TILE map[MAX_GRID_Y][MAX_GRID_X], int tile_x, int tile_y)
{
    TILE *t = &map[tile_y][tile_x];
    return (t != NULL) ? t : NULL;
}

static void editor_clear_screen(ALLEGRO_BITMAP* bmp, ALLEGRO_COLOR col)
{
    al_set_target_bitmap(bmp);
    al_clear_to_color(col);
    al_set_target_backbuffer(get_window_display());
}


static void editor_layer_to_str(EDITOR_LAYER_STATE state)
{


    switch(state){
    case EDITOR_LAYER_BG:
        strncpy(state_text, "(Background Layer)", 65 - 1);
        break;

    case EDITOR_LAYER_MAP:
        strncpy(state_text, "(Map  Layer)",65 - 1);
        break;

    case EDITOR_LAYER_OBJ:
        strncpy(state_text, "(Object Layer)",65 - 1);
        break;

    case EDITOR_LAYER_ALL:
        strncpy(state_text, "(ALL LAYERS)", 65 - 1);
        break;

    }


}

static void editor_tile_put(TILE *map, TILE_ID id)
{
    map->id = (unsigned char) id;
    tiles_set_properties(map);

}
