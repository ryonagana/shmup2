#include "gamestates/CMenuState.h"
#include "imgui.h"
#include "states/IGameState.h"
#include "examples/imgui_impl_allegro5.h"
#include "path.h"

CMenuState::CMenuState()
{
    mapList = std::vector<MENU_PARAM_CALLBACK*>();
    windowNewMap = false;
    windowEditorMode = false;


}


/* LOAD ALL MAPS VIA CALLBACKS*/
int CMenuState::readMapDirCallback(ALLEGRO_FS_ENTRY *dir, void *extra){
    CMenuState *xtra = static_cast<CMenuState*>(extra);


     ALLEGRO_PATH *path = al_create_path(al_get_fs_entry_name(dir));
     std::string menu_name = al_get_path_basename(path);

    MENU_PARAM_CALLBACK *param = new MENU_PARAM_CALLBACK(menu_name,al_get_path_filename(path));


    LOG("Dir Read: %s\nMap Found: %s", param->path.c_str(), param->name.c_str());
    //xtra->menuOpaqueCallbackDir(&xtra->menu_select_map, i++, menu_name);
    xtra->mapList.push_back(new MENU_PARAM_CALLBACK(menu_name, param->path));

    al_destroy_path(path);
    delete param;

    return ALLEGRO_FOR_EACH_FS_ENTRY_OK;
}

bool CMenuState::windowMainMenuDialog()
{
    ImGui::Begin("Main Menu", &windowMainMenu, ImGuiWindowFlags_NoTitleBar |  ImGuiWindowFlags_NoCollapse );                          // Create a window called "Hello, world!" and append into it.

    if(ImGui::Button("New Game")){
            windowMainMenu = false;
            windowSelectMap = true;
    }

    if(ImGui::Button("Editor")){
        windowMainMenu = true;
        windowEditorMode = true;
    }

    if(ImGui::Button("Quit")){
        window_exit_loop();

    }


    ImGui::End();

    return windowMainMenu;
}

bool CMenuState::windowNewGameDialog()
{
    ImGui::Begin("Select Map for Editor:", &windowEditorMode,  ImGuiWindowFlags_NoTitleBar |  ImGuiWindowFlags_NoCollapse );

    if( ImGui::Button("New Map...")){
          LEVEL *lvl = this->mainEngine->getLoadedLevel();
          level_init_default(lvl);
          this->mainEngine->setLevel(lvl);
          windowNewMap = true;


    }

    for(auto m : this->mapList){


        if( ImGui::Button(m->name.c_str())){

           mapSelected = m->name;
           this->mainEngine->loadNewLevel(m->path);

           LOG("MAP SELECTED MENU: %s", m->path.c_str());
           this->mainEngine->setState(GameStateID::Editor); // go to editor

        }
   }

   if(ImGui::Button("Back")){
        windowEditorMode = false;
        windowMainMenu = true;

   }
   ImGui::End();

   return windowEditorMode;
}

bool CMenuState::windowNewGameParamsDialog()
{
    static char buf[1024] = "";
    int h = static_cast<int>(this->mainEngine->getLoadedLevel()->map_width);
    int w = static_cast<int>(this->mainEngine->getLoadedLevel()->map_height);
    bool max_h = false, max_w = false;

    ImGui::Begin("New Map", &windowNewMap,  ImGuiWindowFlags_NoTitleBar);

    ImGui::InputText("Map Name",buf, 1024);
    ImGui::InputInt("Grid Size Width", &w, 1,100);
    ImGui::InputInt("Grid Size Height",&h, 1,100);

    if(w > MAX_GRID_X) max_w = true;
    else max_w = false;

    if(h > MAX_GRID_Y) max_w = true;
    else  max_h = false;

    if(ImGui::Button("Ok")){

        /*
        if(max_w){
            ImGui::Text("Sorry Max Width: %d  ", MAX_GRID_X);

        }else if(max_h){
             ImGui::Text("Sorry Max Height %d  ", MAX_GRID_Y);
        }else {
              windowNewMap = false;
              windowMainMenu = true;
              level_save(this->mainEngine->getLoadedLevel(), "~map_tmp.cbm");
              this->mainEngine->setState(GameStateID::Editor);
        }
        */


         LEVEL *lvl = this->mainEngine->getLoadedLevel();

         std::string new_path = get_file_path("map", buf);
         //level_init_default(lvl);
         lvl->mapname = buf;
         lvl->filename = buf;
         lvl->level_path = new_path;
         level_save(lvl, buf);
         this->mainEngine->loadNewLevel(buf);
         this->mainEngine->setState(GameStateID::Editor);
         windowNewMap = false;
         windowMainMenu = true;

    }

    if(ImGui::Button("Cancel")){
        windowNewMap = false;
    }

    ImGui::End();

    return windowNewMap;
}

bool CMenuState::windowSelectMapDialog()
{
    ImGui::Begin("Select Map", &windowSelectMap);

    for(auto m : this->mapList){


        if( ImGui::Button(m->name.c_str())){
           mapSelected = m->name + ".cbm";
           this->mainEngine->loadNewLevel(mapSelected);
           this->mainEngine->setState(GameStateID::MainGame); // goto game

        }
    }

    if(ImGui::Button("Back")){
        windowSelectMap = false;
        windowMainMenu = true;

    }

    ImGui::End();

    return windowSelectMap;
}

CMenuState::CMenuState(CEngine *parent) : mainEngine(parent)
{

    teste = true;
    windowMainMenu = true;
    windowSelectMap = false;
    windowEditorMode = false;

}


CMenuState::~CMenuState(){

}


void CMenuState::menuOpaqueCallbackDir(MENU *m, int id, const std::string name){
    //menu_add_entry(m,id, name.c_str(), MENU_TYPE_SIMPLE, &this->menuClickSelectMap);
    UNUSED_PARAM(m);
    UNUSED_PARAM(id);
    UNUSED_PARAM((name));
    return;
}

void CMenuState::menuOpaqueClickedLoadMap(MENU *menu, int index)
{
    this->mainEngine->loadNewLevel(menu->entries[static_cast<size_t>(index)].menu);
}


void CMenuState::Init()
{
    menu_init();
    dir.SetPath("map");


    al_for_each_fs_entry(dir.getEntry(), &this->readMapDirCallback,  this);


    state = MENU_OPT_TYPE::MENU_OPT_NONE;

}

void CMenuState::Start()
{

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


    windowMainMenuDialog();



    if(windowSelectMap){
        windowSelectMapDialog();
    }

    if(windowEditorMode){
       windowNewGameDialog();
    }

    if(windowNewMap){
         windowNewGameParamsDialog();
    }

    ImGui::Render();
    al_clear_to_color(al_map_rgb(33,150,243));
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());


}
