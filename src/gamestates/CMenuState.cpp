#include "gamestates/CMenuState.h"
#include "imgui.h"
#include "examples/imgui_impl_allegro5.h"


CMenuState::CMenuState()
{
    mapList = std::vector<MENU_PARAM_CALLBACK*>();

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

    if(windowMainMenu){
        ImGui::Begin("Main Menu", &windowMainMenu, ImGuiWindowFlags_NoTitleBar |  ImGuiWindowFlags_NoCollapse );                          // Create a window called "Hello, world!" and append into it.

        if(ImGui::Button("New Game")){
                windowMainMenu = false;
                windowSelectMap = true;
        }

        if(ImGui::Button("Editor")){
            windowMainMenu = false;
            windowEditorMode = true;
        }

        if(ImGui::Button("Quit")){
            window_exit_loop();

        }


        ImGui::End();

    }

    if(windowSelectMap){
         ImGui::Begin("Select Map", &windowSelectMap);

         for(auto m : this->mapList){
             std::string name = m->name + ".cbm";

             if( ImGui::Button(name.c_str())){
                mapSelected = m->name;
                this->mainEngine->loadNewLevel(m->path);
                this->mainEngine->setState(2); // goto game

             }
         }

         if(ImGui::Button("Back")){
             windowSelectMap = false;
             windowMainMenu = true;

         }

         ImGui::End();
    }

    if(windowEditorMode){
         ImGui::Begin("Select Map for Editor:", &windowEditorMode);
         for(auto m : this->mapList){
             std::string name = m->name + ".cbm";

             if( ImGui::Button(name.c_str())){
                mapSelected = m->name;
                this->mainEngine->loadNewLevel(m->path);
                this->mainEngine->setState(3); // goto editor

             }
        }
        if(ImGui::Button("Back")){
             windowEditorMode = false;
             windowMainMenu = true;

        }
        ImGui::End();
    }

    ImGui::Render();
    al_clear_to_color(al_map_rgb(33,150,243));
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());


}
