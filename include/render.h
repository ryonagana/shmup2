#ifndef RENDER_HEADER
#define RENDER_HEADER

#include <stdio.h>
#include <stdint.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "level.h"

void  render_background_color(LEVEL *level);
void  render_tilemap(LEVEL *level, CAMERA *scroll);



#endif
