#include "spaceship.h"
#include "keyboard.h"
#include "window.h"
#include "level.h"
#include "config.h"
#include "shared.h"


/*
static struct SPACESHIP  player_list[MAX_SPACESHIPS]=
{
        {250,
        100,
        Utils::CRect::Zero(),
        3,3,{0},SPACESHIP_DIRECTION::LEFT,nullptr},

        {250,
         100,
         Utils::CRect::Zero(),
         3,3,{0},SPACESHIP_DIRECTION::LEFT, nullptr}
};
*/


//static ALLEGRO_FONT *debug_txt = nullptr;

//static ALLEGRO_BITMAP *ship_bmp_temp = nullptr;


void spaceship_start(SPACESHIP *ship, CAMERA *ship_camera){
    memset(ship, 0, sizeof(SPACESHIP));
    ship->bmp = al_create_bitmap(32,32);
    al_set_target_bitmap(ship->bmp);
    al_clear_to_color(al_map_rgb(255,0,0));
    al_set_target_backbuffer(GameWindow::getInstance().getDisplay());
    ship->camera = ship_camera;




}

void spaceship_destroy(SPACESHIP *ship){
    if(ship->bmp)
        al_destroy_bitmap(ship->bmp);
}



void spaceship_scrolling_update(SPACESHIP *spaceship, CAMERA *scrolling,  int level_width, int level_height)
{
    int sw = GameWindow::getInstance().getWidth();
    int sh = GameWindow::getInstance().getHeight();

    scrolling->x = spaceship->x + TILE_SIZE / 2  - sw /  2;
    scrolling->y = spaceship->y  + TILE_SIZE / 2 - sh / 2;

    level_width  = level_width  * TILE_SIZE;
    level_height = level_height * TILE_SIZE;

    if(scrolling->x < 0)
    {
        scrolling->x = 0;
    }

    if(scrolling->x > level_width - scrolling->width)
    {
        scrolling->x = level_width - scrolling->width;
    }

    if(scrolling->y < 0)
    {
        scrolling->y = 0;
    }

    if( scrolling->y > (level_height - scrolling->height)){
        scrolling->y = level_height - scrolling->height;
    }


    if(spaceship->x < 0){
        spaceship->x = 0;
    }

    if(spaceship->x > level_width - TILE_SIZE){
        spaceship->x = level_width - TILE_SIZE;
    }

    if(spaceship->y < 0){
        spaceship->y = 0;
    }

    if(spaceship->y > level_height - TILE_SIZE){
        spaceship->y = level_height -  TILE_SIZE ;
    }





}

void spaceship_camera_init(CAMERA *camera, SPACESHIP* ship){
    int sw = GameWindow::getInstance().getWidth();
    int sh = GameWindow::getInstance().getHeight();

    camera->width = sw;
    camera->height = sh;
    camera->x = ship->x + TILE_SIZE / 2  - sw /  2;
    camera->y = ship->y  + TILE_SIZE / 2 - sh / 2;
}

void spaceship_move(SPACESHIP* ship, float x, float y)
{


    ship->x += x * ship->speed_x;
    ship->y += y * ship->speed_y;


    ship->rect.setSize(ship->x - ship->camera ->x , ship->y - ship->camera ->y, al_get_bitmap_width(ship->bmp) + 3 , al_get_bitmap_height(ship->bmp) + 3);


}




bool spaceship_map_limit(SPACESHIP *ship, CAMERA *cam, int level_w, int level_h){

    level_w *= TILE_SIZE;
    level_h *= TILE_SIZE;

    if(cam->x < 0 && ship->x < 0){
       return true;
    }

    if(cam->x > (level_w - cam->width) && ship->x > (level_w - cam->width)){
        return true;
    }

    if(cam->y < 0 && ship->y < 0){
       return true;
    }

    if(cam->y > (level_h - cam->height) && ship->y > (level_h - cam->height)){
        return true;
    }

    return false;
}


void spaceship_update(SPACESHIP *p){



    if(keyboard_pressed(ALLEGRO_KEY_W)){
        spaceship_move(p, 0,-1);
        p->direction = SPACESHIP_DIRECTION::UP;

    }

    if(keyboard_pressed(ALLEGRO_KEY_S)){
        spaceship_move(p,0,1);
         p->direction = SPACESHIP_DIRECTION::DOWN;
    }

    if(keyboard_pressed(ALLEGRO_KEY_A)){
        spaceship_move(p,-1,0);
         p->direction = SPACESHIP_DIRECTION::LEFT;
    }

    if(keyboard_pressed(ALLEGRO_KEY_D)){
        spaceship_move(p,1,0);
         p->direction = SPACESHIP_DIRECTION::RIGHT;
    }

    p->rect.Update();

}

void spaceship_set_default_flags(SPACESHIP *sp){

    sp->flags.alive      |= 1;
    sp->flags.controlled |= 1;
    sp->flags.controlled |= 0;
    sp->flags.collision  |= 0;

}

void spaceship_draw(SPACESHIP *ship, CAMERA *cam)
{
   al_draw_bitmap(ship->bmp, ship->x - cam->x , ship->y - cam->y,0);

   if( ship->flags.collision  ){
    al_draw_text(GameWindow::getInstance().getDebugFont(), al_map_rgb(255,0,0), ship->x - cam->x , (ship->y - cam->y) - 25 , 0, "collision");
   }
   al_draw_rectangle(ship->rect.X(),ship->rect.Y(), (ship->rect.X() + TILE_SIZE), (ship->rect.Y() + TILE_SIZE), al_map_rgb(0,0,255),1);
}

SPACESHIP *spaceship_get(std::vector<SPACESHIP> &&ships, int num)
{
    return &ships[num];
}
