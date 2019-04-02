#ifndef SPACESHIP_HEADER
#define SPACESHIP_HEADER
#include <cstdio>
#include "window.h"
#include "level.h"
#include "Utils/CRect.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define SHIP_P1 (0)
#define SHIP_P2 (1)

#define MAX_SPACESHIPS (2) //leading zero


typedef enum class SPACESHIP_DIRECTION : int {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    DIAGONAL_LEFT_UP,
    DIAGONAL_RIGHT_UP,
    DIAGONAL_LEFT_DN,
    DIAGONAL_RIGHT_DN
}SPACESHIP_DIRECTION;

typedef struct {
    uint32_t controlled: 1;
    uint32_t god_mode: 1;
    uint32_t alive: 1;
    uint32_t cheat: 1;
    uint32_t collision: 1;
}SPACESHIP_FLAG;

typedef struct CAMERA {
    float x,y;
    int width,height;
}CAMERA;


typedef struct SPACESHIP{
    float x;
    float y;
    sf::Rect<float> rect;
    float speed;

    union {
        uint32_t all_flags;
        SPACESHIP_FLAG flags;
    };
    SPACESHIP_DIRECTION direction;
    CAMERA *camera;



} SPACESHIP;



void spaceship_start(SPACESHIP *ship, CAMERA *ship_camera);
void spaceship_destroy(void);
void spaceship_move(sf::Time elapsed, int num,   float x, float y);
SPACESHIP* spaceship_get_player(int num);
void spaceship_update(sf::Time elapsed, int player_num);
bool spaceship_map_limit(SPACESHIP *ship, CAMERA *cam, int level_w, int level_h);
void spaceship_set_default_flags(SPACESHIP *sp);
void spaceship_draw(sf::RenderWindow *win, SPACESHIP *ship, CAMERA *cam);

void spaceship_camera_init(float x, float y, CAMERA *camera, SPACESHIP* ship);
void spaceship_scrolling_update(sf::Time elapsed, sf::RenderWindow *window, SPACESHIP *spaceship, CAMERA *scrolling,  int level_width, int level_height);

#endif
