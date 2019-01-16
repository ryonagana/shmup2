#include "editor.h"


static EDITOR *editor = NULL;
static bool opened_dialog = false;
static ALLEGRO_BITMAP *editor_cursor = NULL;


static ALLEGRO_BITMAP *canvas_screen = NULL;
static ALLEGRO_BITMAP *tools_screen  = NULL;

static void editor_move_camera(float x, float y);
static void editor_clear_screen(ALLEGRO_BITMAP* bmp);
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

    char *path = get_file_path("tile", "editor_cursor.png");

    editor_cursor = al_load_bitmap(path);

    if(editor_cursor == NULL){
        editor_cursor = al_create_bitmap(TILE_SIZE,TILE_SIZE);
        al_set_target_bitmap(editor_cursor);
        al_draw_rectangle(0,0,32,32,al_map_rgb(255,0,0),1.0);
        al_set_target_backbuffer(get_window_display());
    }


    canvas_screen = al_create_bitmap( 18 * TILE_SIZE , 18 * TILE_SIZE );
    tools_screen = al_create_bitmap( 200, al_get_display_width(get_window_display()));

    editor_clear_screen(canvas_screen);
    editor_clear_screen(tools_screen);


    if(path)free(path);



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

    if( (mouse_get()->x / TILE_SIZE) > 17){
        return;
    }

    if( (mouse_get()->y / TILE_SIZE) > 17){
        return;
    }



    int world_x = editor->camera->x + mouse_get()->x;
    int world_y = editor->camera->y + mouse_get()->y;
    int tile_x = world_x / TILE_SIZE;
    int tile_y = world_y / TILE_SIZE;





    if(mouse_get()->lButton){
        //TILE *t = editor_tile_get(&editor->level->map_layer[MAX_GRID_Y][MAX_GRID_X], tile_x, tile_y);
        printf("\nTILE: x: %d y: %d id: %d\n", tile_x, tile_y, 0);
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




    //al_draw_rectangle(editor->level->map_width * TILE_SIZE, editor->level->map_height * TILE_SIZE, (editor->level->map_width * TILE_SIZE) - editor->camera->x, (editor->level->map_height* TILE_SIZE) - editor->camera->y, al_map_rgb(0,255,0),2.0);

    al_set_target_bitmap(canvas_screen);

    for(int y = 0; y < MAX_GRID_Y; y++){
         for(int x = 0; x < MAX_GRID_X; x++){

             if( x < editor->level->map_width && y < editor->level->map_height){
                al_draw_bitmap( tiles_get_by_id(editor->level->map_layer[y][x].id ), (TILE_SIZE * x) - editor->camera->x, (TILE_SIZE * y) - editor->camera->y,0);
                al_draw_rectangle(x * TILE_SIZE, y * TILE_SIZE, (x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE, al_map_rgb(0,0,153),1.0);
             }
         }
    }

    al_set_target_backbuffer(get_window_display());


   //al_draw_bitmap_region(canvas_screen,editor->camera->x,editor->camera->y, al_get_bitmap_width(canvas_screen), al_get_bitmap_height(canvas_screen),editor->camera->x,editor->camera->y,0);
   al_draw_bitmap(canvas_screen,0,0,0);


   al_draw_bitmap(editor_cursor, editor->editor_rect.x1, editor->editor_rect.y1, 0);

}


void editor_destroy(void){
    if(editor->camera) free(editor->camera);
    editor->camera = NULL;

    if(editor) free(editor);
    editor = NULL;

    if(editor_cursor) al_destroy_bitmap(editor_cursor);
    if(canvas_screen) al_destroy_bitmap(canvas_screen);
    if(tools_screen) al_destroy_bitmap(tools_screen);


}


static void editor_move_camera(float x, float y){
    editor->camera->x +=  TILE_SIZE * x;
    editor->camera->y +=  TILE_SIZE * y;

    if(editor->camera->x < 0) editor->camera->x = 0;
    if(editor->camera->y < 0) editor->camera->y = 0;

}

static void editor_camera_bounds(void){




    if(editor->camera->x < 0)  editor->camera->x = 0;

    if(editor->camera->x > MAX_GRID_Y * TILE_SIZE){
        editor->camera->x =  editor->level->map_width * TILE_SIZE ;
    }

     if(editor->camera->y < 0)  editor->camera->y = 0;

     if(editor->camera->y > MAX_GRID_Y * TILE_SIZE){
         editor->camera->y =  editor->level->map_height  * TILE_SIZE ;
     }




}

static TILE *editor_tile_get(TILE *map[MAX_GRID_Y][MAX_GRID_X],  int x, int y){
    return map[y][x];
}

static void editor_clear_screen(ALLEGRO_BITMAP* bmp){
    al_set_target_bitmap(bmp);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_set_target_backbuffer(get_window_display());
}
