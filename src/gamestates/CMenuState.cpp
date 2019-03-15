#include "gamestates/CMenuState.h"
#include "imgui.h"
#include "examples/imgui_impl_allegro5.h"

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


   LOG("CLICKED MAP");
    return false;
}

CMenuState::CMenuState()
{

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


    LOG("Dir Read: %s\nMap Found: %s", param->path.c_str(), param->name.c_str());
    xtra->menuOpaqueCallbackDir(&xtra->menu_select_map, i++, menu_name);


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

CMenuState::CMenuState(CEngine *parent) : mainEngine(parent)
{

    teste = true;
    windowMainMenu = true;
    windowSelectMap = false;

}


CMenuState::~CMenuState(){

}


void CMenuState::menuOpaqueCallbackDir(MENU *m, int id, const std::string name){
    menu_add_entry(m,id, name.c_str(), MENU_TYPE_SIMPLE, &this->menuClickSelectMap);
    return;
}

void CMenuState::menuOpaqueClickedLoadMap(MENU *menu, int index)
{
    this->mainEngine->loadNewLevel(menu->entries[static_cast<size_t>(index)].menu);
}

void CMenuState::resetMenuState()
{
    this->state = MENU_OPT_TYPE::MENU_OPT_NONE;
}

void CMenuState::Init()
{
    menu_init();
    dir.SetPath("map");

    // access static members to non static you must pass the pointer
    // is this  a bad pratice?

    menu_create(&main_menu, 10);
    menu_add_entry(&main_menu, 1, "NEW GAME", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickNewGame, this, std::placeholders::_1));
    menu_add_entry(&main_menu, 2, "MAP EDITOR", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickEditor, this, std::placeholders::_1));
    menu_add_entry(&main_menu, 3, "LOAD..", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickEditor, this, std::placeholders::_1));
    menu_add_entry(&main_menu, 4, "SAVE..", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickEditor, this, std::placeholders::_1));
    menu_add_entry(&main_menu, 4, "ABOUT", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickEditor, this, std::placeholders::_1));
    menu_add_entry(&main_menu, 5, "QUIT", MENU_TYPE_SIMPLE, std::bind(&CMenuState::menuClickQuit, this, std::placeholders::_1));

    MENU_PARAM_CALLBACK params;

    text_init(&credits, nullptr, 25);


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
    resetMenuState();
}

void CMenuState::Destroy()
{
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
}

void CMenuState::Update(ALLEGRO_EVENT *e)
{




    if(e->type == ALLEGRO_EVENT_DISPLAY_RESIZE){
         ImGui_ImplAllegro5_InvalidateDeviceObjects();
         al_acknowledge_resize(get_window_display());
         ImGui_ImplAllegro5_CreateDeviceObjects();
    }



    /*
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
    */
}

void CMenuState::HandleInput(ALLEGRO_EVENT *e){


     ImGui_ImplAllegro5_ProcessEvent(e);


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

    ImGui_ImplAllegro5_NewFrame();
    ImGui::NewFrame();

    if(windowMainMenu){
        ImGui::Begin("Main Menu", &windowMainMenu, ImGuiWindowFlags_NoTitleBar |  ImGuiWindowFlags_NoCollapse );                          // Create a window called "Hello, world!" and append into it.

        if(ImGui::Button("New Game")){
                windowMainMenu = false;
                windowSelectMap = true;
        }

        if(ImGui::Button("Editor")){

        }

        if(ImGui::Button("Quit")){
            window_exit_loop();

        }


        ImGui::End();

    }

    if(windowSelectMap){
         ImGui::Begin("Select Map", &windowSelectMap);

         if(ImGui::Button("Quit")){
             windowSelectMap = false;
             windowMainMenu = true;

         }

         ImGui::End();
    }

    ImGui::Render();
    al_clear_to_color(al_map_rgb(33,150,243));
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

    /*
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
    */

   // text_draw(&credits, al_map_rgb(255,0,0), (window_get_width() / 2) + 100 , window_get_height() - 50, "by ArchDark\n And JRCL - 2019");

}
