#ifndef PATH_HEADER
#include <stdio.h>
#include <allegro5/allegro5.h>


void init_path(void);
void destroy_path(void);
ALLEGRO_PATH* get_root_path(void);


const char* get_root_dir(void);
const char* get_file_path(const char *folder, const char *filename);

#endif
