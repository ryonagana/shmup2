#include "path.h"

const char* get_root_dir(void){
      ALLEGRO_PATH* resource_path = NULL;
      resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      const char* path = al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP);
      al_destroy_path(resource_path);
      return path;
}

const char* get_file_path(const char *folder, const char *filename){

    ALLEGRO_PATH* resource_path = NULL;

    resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

    al_append_path_component(resource_path, folder);
    al_set_path_filename(resource_path, filename);
    const char* path = al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP);
    al_destroy_path(resource_path);

    return path;
}
