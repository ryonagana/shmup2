#ifndef RENDER_HEADER
#define RENDER_HEADER

#include <cstdio>
#include <cstdint>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "level.h"



void  render_start(LEVEL *level);
void  render_background_color(LEVEL *level);
void  render_tilemap(LEVEL *level, CAMERA *scroll, SPACESHIP *ship);
void  render_destroy();



#endif
