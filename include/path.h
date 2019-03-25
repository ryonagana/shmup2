#ifndef PATH_HEADER
#define PATH_HEADER

#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <allegro5/allegro5.h>


void init_path(void);
void destroy_path(void);
ALLEGRO_PATH* get_root_path(void);


const char* get_root_dir(void);
char* get_file_path(const char *folder, const char *filename);
std::string  get_file_path_str(const std::string folder, const std::string filename);

#endif
