#include "path.h"


static ALLEGRO_PATH *root_path = NULL;

void init_path(void){
    root_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
}

void destroy_path(void){
    if(root_path) al_destroy_path(root_path);
}

ALLEGRO_PATH* get_root_path(void){
    return root_path != NULL ? root_path : NULL;
}


const char* get_root_dir(void){

      const char* path = al_path_cstr(root_path, ALLEGRO_NATIVE_PATH_SEP);
      return path;
}

char* get_file_path(const char *folder, const char *filename){

    ALLEGRO_PATH *root = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

    if(folder != NULL ){
        al_append_path_component(root, folder);
    }

    al_set_path_filename(root, filename);
    const char* path = al_path_cstr(root, ALLEGRO_NATIVE_PATH_SEP);
    char *copy_path = (char *) malloc(sizeof (char) * strlen(path) + 1);
    memset(copy_path,0, sizeof (char) * strlen(path) + 1);

    strncpy(copy_path, path, strlen(path));
    al_destroy_path(root);
    return copy_path;
}
