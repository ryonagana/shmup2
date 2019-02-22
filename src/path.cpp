#include "path.h"


static ALLEGRO_PATH *root_path = nullptr;

void init_path(void){
    root_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
}

void destroy_path(void){
    if(root_path) al_destroy_path(root_path);
}

ALLEGRO_PATH* get_root_path(void){
    return root_path != nullptr ? root_path : nullptr;
}


const char* get_root_dir(void){

      const char* path = al_path_cstr(root_path, ALLEGRO_NATIVE_PATH_SEP);
      return path;
}

char* get_file_path(const char *folder, const char *filename){
    char *copy_path = nullptr;
    const char* path = nullptr;
    ALLEGRO_PATH *root = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

    if(folder != nullptr ){
        al_append_path_component(root, folder);
    }

    al_set_path_filename(root, filename);
    path = al_path_cstr(root, ALLEGRO_NATIVE_PATH_SEP);

    copy_path = new char[ strlen(path) + 1 ]; //(char *) malloc(sizeof (char) * strlen(path) + 1);
    memset(copy_path,0, sizeof (char) * strlen(path) + 1);

    strncpy(copy_path, path, strlen(path));
    al_destroy_path(root);
    return copy_path;
}
