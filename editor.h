#ifndef EDITOR_HEADER
#define EDITOR_HEADER
#include <stdio.h>
#include "window.h"
#include <allegro5/allegro.h>
#include "keyboard.h"
#include "level.h"
#include "window.h"
#include "tiles.h"
#include "config.h"
#include "mouse.h"
#include "shared.h"

typedef struct CAMERA_EDITOR {
    int x,y;
    int width,height;
}CAMERA_EDITOR;


typedef enum EDITOR_STATE {
    EDITOR_STATE_INIT,
    EDITOR_STATE_EDIT,
    EDITOR_STATE_SAVE,
    EDITOR_STATE_LOAD,
}EDITOR_STATE;


typedef enum EDITOR_LAYER_STATE {
    EDITOR_LAYER_BG=100,
    EDITOR_LAYER_MAP,
    EDITOR_LAYER_OBJ
}EDITOR_LAYER_STATE;

typedef struct EDITOR_RECT {
    float x1,x2,y1,y2;
}EDITOR_RECT;

typedef struct EDITOR{
    LEVEL *level;
    EDITOR_STATE state;
    TILE_ID old_selected_tile;
    TILE_ID selected_tile;
    CAMERA_EDITOR *camera;
    EDITOR_RECT editor_rect;


}EDITOR;

void editor_init(void);
bool editor_load(LEVEL *level);
void editor_update_keyboard(ALLEGRO_EVENT *e);
void editor_update(ALLEGRO_EVENT *e);
void editor_render(void);
void editor_map_to_coord(void);
void editor_destroy(void);


#endif
