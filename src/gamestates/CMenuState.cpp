#include "gamestates/CMenuState.h"




bool CMenuState::menuClickNewGame(int id){
    UNUSED_PARAM(id);
    state = MENU_OPT_TYPE::MENU_OPT_NEW_GAME;
    printf("Click\n");
    return false;
}


bool CMenuState::menuClickEditor(int id){
    UNUSED_PARAM(id);


    return false;
}

bool  CMenuState::menuClickQuit(int id){
    UNUSED_PARAM(id);

    window_exit_loop();
    return false;
}



bool CMenuState::menuClickMapList(int id)
{
    std::string menu_name =  this->menu_select_map.entries[id].menu;
    menu_name += ".cbm";


    return false;
}

bool CMenuState::menuClickMapListEditor(int id){
    std::string menu_name = this->menu_select_map.entries[id].menu;
    menu_name += ".cbm";

   return false;
}


bool CMenuState::menuClickSelectMap(int id)
{
    return false;
}


/* LOAD ALL MAPS VIA CALLBACKS*/
int CMenuState::readMapDirCallback(ALLEGRO_FS_ENTRY *dir, void *extra){
    CMenuState *xtra = static_cast<CMenuState*>(extra);
    static int i = 0;

     ALLEGRO_PATH *path = al_create_path(al_get_fs_entry_name(dir));
     std::string menu_name = al_get_path_basename(path);

    MENU_PARAM_CALLBACK *param = new MENU_PARAM_CALLBACK;


    param->name = menu_name;
    param->path = al_get_path_filename(path);


    xtra->menuMapDirCallbackF(&xtra->menu_select_map, i++, menu_name);


    al_destroy_path(path);

     /*
     MENU_PARAM_CALLBACK *menu = static_cast<MENU_PARAM_CALLBACK*>(extra);
     CMenuState cstate(menu->self->engine);


     cstate = *menu->self;



    UNUSED_PARAM(extra);
    static int i = 0;
    ALLEGRO_PATH *path = al_create_path(al_get_fs_entry_name(dir));

    std::string menu_name = al_get_path_basename(path);
    menu_add_entry(menu->menu,i++, menu_name.c_str(), MENU_TYPE_SIMPLE, nullptr);
    al_destroy_path(path);
    */
    return ALLEGRO_FOR_EACH_FS_ENTRY_OK;
}

CMenuState::CMenuState() : CMenuState(nullptr) {

}

CMenuState::CMenuState(CEngine *parent) : engine(parent){

}

CMenuState::~CMenuState(){

}


void CMenuState::menuMapDirCallbackF(MENU *m, int id, const std::string name){
    menu_add_entry(m,id, name.c_str(), MENU_TYPE_SIMPLE, &this->menuClickSelectMap);
    return;
}

void CMenuState::Init()
{
    menu_init();
    dir.SetPath("map");

    // access static members to non static you must pass the pointer
    // is this  a bad pratice?

    menu_create(&main_menu, 5);
    menu_add_entry(&main_menu, 1, "TESTE", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickNewGame, this, std::placeholders::_1));
    menu_add_entry(&main_menu, 2, "MAP EDITOR", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickEditor, this, std::placeholders::_1));
    menu_add_entry(&main_menu, 2, "QUIT", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickQuit, this, std::placeholders::_1));

    MENU_PARAM_CALLBACK params;



    menu_create(&menu_select_map,10);
    al_for_each_fs_entry(dir.getEntry(), &this->readMapDirCallback,  this);

   // menu_create(&menu_select_map_editor,10);
   // al_for_each_fs_entry(dir.getEntry(), &this->readMapDirCallback, this);







    //al_for_each_fs_entry(dir.getEntry(), std::move(&this->readMapDirCallback), nullptr);


    //CMenuState::s_map_editor = &menu_select_map_editor;
    //CMenuState::s_new_map    = &menu_select_map;

    state = MENU_OPT_TYPE::MENU_OPT_NONE;

}

void CMenuState::Start()
{
}

void CMenuState::Destroy()
{
}

void CMenuState::Update(ALLEGRO_EVENT *e)
{


    switch(state){
        case MENU_OPT_TYPE::MENU_OPT_NEW_GAME:
        menu_update(&this->menu_select_map, e);
        break;

    case MENU_OPT_TYPE::MENU_OPT_EDITOR:
         menu_update(&this->menu_select_map_editor, e);
        break;

    case MENU_OPT_TYPE::MENU_OPT_NONE:
    default:
        menu_update(&this->main_menu, e);
        break;

    }
}

void CMenuState::UpdateInput(ALLEGRO_EVENT *e){

    if(e->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(e->mouse.button & 1){
            mouse_get()->lButton = true;
        }
    }

    if(e->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        if(e->mouse.button & 1){
            mouse_get()->lButton = false;
        }
    }

    if(e->type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_get()->x = e->mouse.x;
        mouse_get()->y = e->mouse.y;
        mouse_get()->z = e->mouse.dz;
    }

}

void CMenuState::Draw()
{
    al_clear_to_color(al_map_rgb(0,0,0));

    switch(state){
        case MENU_OPT_TYPE::MENU_OPT_NEW_GAME:
          menu_draw(&this->menu_select_map);
        break;

    case MENU_OPT_TYPE::MENU_OPT_EDITOR:
          menu_draw(&this->menu_select_map_editor);
        break;

    case MENU_OPT_TYPE::MENU_OPT_NONE:
    default:
          menu_draw(&this->main_menu);
        break;

    }

}
