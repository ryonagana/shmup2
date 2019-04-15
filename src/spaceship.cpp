#include "spaceship.h"
#include "shared.h"
#include "tiles.h"


static struct SPACESHIP  player_list[MAX_SPACESHIPS]=
{
        {0,
        0,
        {0,0,0,0},
        140,{0},SPACESHIP_DIRECTION::LEFT,nullptr},

        {0,
         0,
         {0,0,0,0},
         1,{0},SPACESHIP_DIRECTION::LEFT, nullptr}
};


static sf::RectangleShape ship_spr;


void spaceship_start(SPACESHIP *ship, CAMERA *ship_camera){

    UNUSED_PARAM(ship);
    UNUSED_PARAM((ship_camera));
    ship_spr.setSize(sf::Vector2f(32,32));
    ship_spr.setFillColor(sf::Color(255,0,0));
    ship_spr.setPosition(player_list[SHIP_P1].x,player_list[SHIP_P1].y);

}

void spaceship_destroy(void){

}



void spaceship_scrolling_update(sf::Time elapsed, sf::RenderWindow *window, SPACESHIP *spaceship, CAMERA *scrolling,  int level_width, int level_height)
{
    scrolling->x = (spaceship->x + TILE_SIZE / 2  - window->getSize().x /  2);
    scrolling->y = (spaceship->y  + TILE_SIZE / 2 - window->getSize().y / 2);

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

void spaceship_camera_init(float x, float y, CAMERA *camera, SPACESHIP* ship){
    camera->width = static_cast<int>(x);
    camera->height = static_cast<int>(y);
    camera->x = ship->x + TILE_SIZE / 2  - static_cast<int>(x) /  2;
    camera->y = ship->y  + TILE_SIZE / 2 - static_cast<int>(y) / 2;
}

void spaceship_move(sf::Time elapsed, int num,   float x, float y)
{
    struct SPACESHIP* player = nullptr;
    player = spaceship_get_player(num);

    player->x += x * player->speed * elapsed.asSeconds();
    player->y += y * player->speed * elapsed.asSeconds();

    ship_spr.setPosition(player->x, player->y);
    //player->rect.setSize(player->x - player->camera ->x ,player->y - player->camera ->y, al_get_bitmap_width(ship_bmp_temp) + 3 , al_get_bitmap_height(ship_bmp_temp) + 3);


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


void spaceship_update(sf::Time elapsed, int player_num){

    SPACESHIP *p = spaceship_get_player(player_num);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ){
        spaceship_move(elapsed, player_num, 0,-1);
        p->direction = SPACESHIP_DIRECTION::UP;

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        spaceship_move(elapsed, player_num,0,1);
         p->direction = SPACESHIP_DIRECTION::DOWN;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        spaceship_move(elapsed, player_num,-1,0);
         p->direction = SPACESHIP_DIRECTION::LEFT;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        spaceship_move(elapsed, player_num,1,0);
         p->direction = SPACESHIP_DIRECTION::RIGHT;
    }
}

void spaceship_set_default_flags(SPACESHIP *sp){

    sp->flags.alive      |= 1;
    sp->flags.controlled |= 1;
    sp->flags.controlled |= 0;
    sp->flags.collision  |= 0;

}

void spaceship_draw(sf::RenderWindow *win, SPACESHIP *ship, CAMERA *cam)
{
    if(!win){
        LOG("Missing Window Ptr.");
        return;
    }

    win->draw(ship_spr);

   /*
   al_draw_bitmap(ship_bmp_temp, ship->x - cam->x , ship->y - cam->y,0);

   if( ship->flags.collision  ){
    al_draw_text(debug_txt, al_map_rgb(255,0,0), ship->x - cam->x , (ship->y - cam->y) - 25 , 0, "collision");
   }
   al_draw_rectangle(ship->rect.getX(),ship->rect.getY(), ship->rect.getX() + TILE_SIZE, ship->rect.getY() + TILE_SIZE, al_map_rgb(0,0,255),1);
   */
}
