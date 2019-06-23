#include "spaceship.h"
#include "keyboard.h"
#include "window.h"
#include "level.h"
#include "config.h"
#include "shared.h"

static struct SPACESHIP  player_list[MAX_SPACESHIPS]=
{
        {250,
        100,
        Utils::CRect::Zero(),
        3,{0},SPACESHIP_DIRECTION::LEFT,nullptr},

        {250,
         100,
         Utils::CRect::Zero(),
         3,{0},SPACESHIP_DIRECTION::LEFT, nullptr}
};


static ALLEGRO_FONT *debug_txt = nullptr;

static ALLEGRO_BITMAP *ship_bmp_temp = nullptr;


void spaceship_start(SPACESHIP *ship, CAMERA *ship_camera){
    ship_bmp_temp = al_create_bitmap(32,32);
    al_set_target_bitmap(ship_bmp_temp);
    al_clear_to_color(al_map_rgb(255,0,0));
    al_set_target_backbuffer(get_window_display());
    ship->camera = ship_camera;

    if(!debug_txt){
        debug_txt = al_create_builtin_font();
    }


    player_list[SHIP_P1].rect.setSize(player_list[SHIP_P1].x,player_list[SHIP_P1].y, al_get_bitmap_width( ship_bmp_temp), al_get_bitmap_height( ship_bmp_temp) );
    player_list[SHIP_P2].rect.setSize(player_list[SHIP_P2].x,player_list[SHIP_P2].y, al_get_bitmap_width( ship_bmp_temp), al_get_bitmap_height( ship_bmp_temp) );


    ship->rect.x = player_list[SHIP_P1].x;
    ship->rect.y = player_list[SHIP_P1].y;


}

void spaceship_destroy(void){
    if(ship_bmp_temp) al_destroy_bitmap(ship_bmp_temp);
}



void spaceship_scrolling_update(SPACESHIP *spaceship, CAMERA *scrolling,  int level_width, int level_height)
{
    scrolling->x = spaceship->x + TILE_SIZE / 2  - window_get_width() /  2;
    scrolling->y = spaceship->y  + TILE_SIZE / 2 - window_get_height() / 2;

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
    camera->width = window_get_width();
    camera->height = window_get_height();
    camera->x = ship->x + TILE_SIZE / 2  - window_get_width() /  2;
    camera->y = ship->y  + TILE_SIZE / 2 - window_get_height() / 2;
}

void spaceship_move(int num,   float x, float y)
{
    struct SPACESHIP* player = nullptr;
    player = spaceship_get_player(num);

    player->x += x * player->speed;
    player->y += y * player->speed;


    player->rect.setSize(player->x - player->camera ->x ,player->y - player->camera ->y, al_get_bitmap_width(ship_bmp_temp) + 3 , al_get_bitmap_height(ship_bmp_temp) + 3);


}


SPACESHIP *spaceship_get_player(int num){
    if(num > MAX_SPACESHIPS) return nullptr;
    return &player_list[num] != nullptr ? &player_list[num] : nullptr;
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


void spaceship_update(int player_num){

    SPACESHIP *p = spaceship_get_player(player_num);

    if(keyboard_pressed(ALLEGRO_KEY_W)){
        spaceship_move(player_num, 0,-1);
        p->direction = SPACESHIP_DIRECTION::UP;

    }

    if(keyboard_pressed(ALLEGRO_KEY_S)){
        spaceship_move(player_num,0,1);
         p->direction = SPACESHIP_DIRECTION::DOWN;
    }

    if(keyboard_pressed(ALLEGRO_KEY_A)){
        spaceship_move(player_num,-1,0);
         p->direction = SPACESHIP_DIRECTION::LEFT;
    }

    if(keyboard_pressed(ALLEGRO_KEY_D)){
        spaceship_move(player_num,1,0);
         p->direction = SPACESHIP_DIRECTION::RIGHT;
    }


}

void spaceship_set_default_flags(SPACESHIP *sp){

    sp->flags.alive      |= 1;
    sp->flags.controlled |= 1;
    sp->flags.controlled |= 0;
    sp->flags.collision  |= 0;

}

void spaceship_draw(SPACESHIP *ship, CAMERA *cam)
{
   al_draw_bitmap(ship_bmp_temp, ship->x - cam->x , ship->y - cam->y,0);

   if( ship->flags.collision  ){
    al_draw_text(debug_txt, al_map_rgb(255,0,0), ship->x - cam->x , (ship->y - cam->y) - 25 , 0, "collision");
   }
   al_draw_rectangle(ship->rect.X() - 5,ship->rect.Y() - 5, (ship->rect.X() + TILE_SIZE) + 5, (ship->rect.Y() + TILE_SIZE) + 5, al_map_rgb(0,0,255),1);
}
