#include "mouse.h"

static MOUSE *mouse_input = NULL;

void mouse_init(void){
    if(mouse_input == NULL){
        mouse_input = (MOUSE*) malloc(sizeof(MOUSE));
    }

    mouse_input->lButton = false;
    mouse_input->rButton = false;
    mouse_input->x = 0.0f;
    mouse_input->y = 0.0f;
    mouse_input->z = 0.0;

}


void mouse_destroy(void){
    if(mouse_input) free(mouse_input);
    mouse_input = NULL;
}


MOUSE *mouse_get(void){
    if(!mouse_input) return NULL;
    return mouse_input;
}

void mouse_update(ALLEGRO_EVENT *e){
    if(e->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        if(e->mouse.button & 1){
            mouse_input->lButton = true;
        }

     if(e->mouse.button    & 2){
            mouse_input->rButton = true;
        }
    }

    if(e->type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_input->z = (double) e->mouse.dz;
    }
}
