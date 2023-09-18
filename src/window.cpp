#include "window.h"
#include "keyboard.h"
#include "mixer.h"
#include "path.h"
#include "shared.h"
#include "tiles.h"
#include "config.h"
#include "mouse.h"
#include "editor.h"
#include "tiles.h"
#include "imgui.h"
#include "GUI/imgui_impl_allegro5.h"



#define WINDOW_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define WINDOW_LOG(...) fprintf(stdout, __VA_ARGS__)

GameWindow::GameWindow() :
    m_width(800),
    m_height(600),
    m_window_title("Default App"),
    m_fullscreen(false),
    m_vsync(false),
    m_render_flags(0),
    m_window_started(false),
    m_is_running(true),
    m_is_destroyed(false)
{

}

int GameWindow::allegroInit()
{
    int error = 0;

    if(!al_init()){
        WINDOW_ERROR("Allegro Cant Init! Sorry!\n");
        error++;
    }

    if(!al_install_keyboard()){
         WINDOW_ERROR("keyboard not Installed!\n");
          error++;
    }

    if(!al_install_mouse()){
        WINDOW_ERROR("keyboard not Installed!\n");
         error++;
    }


    if(!al_install_joystick()){
        WINDOW_ERROR("keyboard not Installed!\n");
         error++;
    }


    if(!al_init_image_addon()){
        WINDOW_ERROR("Allegro Image Add-on Failed\n");
         error++;
    }

    if(!al_init_acodec_addon() || !al_install_audio()){
        WINDOW_ERROR("Allegro Sound Failed");
         error++;
    }

    if(!al_init_font_addon() || !al_init_ttf_addon()){
        WINDOW_ERROR("Allegro Image Add-on Failed\n");
         error++;
    }

    if(!al_init_primitives_addon()){
        WINDOW_ERROR("Allegro Primitives Add-on Failed\n");
         error++;
    }


    if(!al_init_native_dialog_addon()){
        WINDOW_ERROR("Allegro Dialog Add-on Failed\n");
         error++;
    }


    return error;
}

void GameWindow::setRender(int type)
{
    switch(type){
        case RenderType::OPENGL:
            m_render_flags |= ALLEGRO_OPENGL_3_0 | ALLEGRO_PROGRAMMABLE_PIPELINE;
            break;
        case RenderType::OPENGL_NEW:
            m_render_flags |= ALLEGRO_OPENGL_FORWARD_COMPATIBLE | ALLEGRO_PROGRAMMABLE_PIPELINE;
            break;

       case RenderType::DIRECT3D:
            m_render_flags |= ALLEGRO_DIRECT3D_INTERNAL;
    }
}

int GameWindow::createDisplay(int width, int height, bool fullscreen, bool vsync, double fps, int render_type,  const std::string &window_title, int flags)
{
    int window_flags = flags;

    if(fullscreen){
        window_flags |= ALLEGRO_FULLSCREEN_WINDOW;
        m_fullscreen = true;
    }

    if(vsync){
        al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
    }

    if(fps <= 0){
        fps =  DESIRED_FPS;
    }else {
        fps = 1.0/fps;
    }

    setRender(render_type);

    m_window_title = window_title;
    al_set_new_display_flags(window_flags | m_render_flags);
    al_set_new_window_title(window_title.c_str());
    m_display = al_create_display(width, height);


    if(!m_display){
        WINDOW_ERROR("%s: Display Error", __func__);
        return 0;
    }

    m_queue = al_create_event_queue();

    if(!m_queue){
        WINDOW_ERROR("%s: Queue Error", __func__);
        return 0;
    }

    m_timer = al_create_timer(fps);

    if(!m_timer){
        WINDOW_ERROR("%s: Timer Error", __func__);
        return 0;
    }

    m_debug_font  = al_create_builtin_font();

    if(!m_debug_font){
        WINDOW_ERROR("%s: builtin font error Error", __func__);
        return 0;
    }


    //register events
    al_register_event_source(m_queue, al_get_display_event_source(m_display));
    al_register_event_source(m_queue, al_get_keyboard_event_source());
    al_register_event_source(m_queue, al_get_mouse_event_source());
    al_register_event_source(m_queue, al_get_joystick_event_source());
    al_register_event_source(m_queue, al_get_timer_event_source(m_timer));

    al_start_timer(m_timer);


    return 1;

}

void GameWindow::Destroy()
{
    if(m_display){
        al_destroy_display(m_display);
        m_display =  nullptr;
    }

    if(m_queue){
        al_destroy_event_queue(m_queue);
        m_queue =  nullptr;
    }

    if(m_timer){
        al_destroy_timer(m_timer);
        m_timer =  nullptr;
    }

    if(m_screen){
        al_destroy_bitmap(m_screen);
        m_screen =  nullptr;
    }

    if(m_debug_font){
        al_destroy_font(m_debug_font);
        m_debug_font = nullptr;
    }

    m_is_destroyed = true;
}

void GameWindow::Quit(const std::string &message)
{
    if(!m_is_destroyed){
        this->Destroy();
    }

    al_uninstall_audio();
    al_uninstall_joystick();
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_system();
    WINDOW_LOG(message.c_str());
    return;
}


#if 0
static ALLEGRO_EVENT_QUEUE *g_queue = nullptr;
static ALLEGRO_DISPLAY *g_display = nullptr;
static ALLEGRO_KEYBOARD_STATE g_kbdstate;
static ALLEGRO_BITMAP *g_screen = nullptr;
static ALLEGRO_TIMER *g_timer = nullptr;
static ALLEGRO_TIMER *g_time  = nullptr;








static bool is_window_open = false;
static bool issue_gracefully_close = false;


static int64_t timer_milliseconds = 0;


static int init_allegro(void) {


    if (!al_init()){
        CRITICAL("Error: Cannot Initialize Allegro :-(");

        //DEBUG_PRINT("Error: Cannot Initialize Allegro :-(");
        return -1;

    }

    if(!al_install_keyboard()){
        CRITICAL("Error: Cannot Install Keyboard");
        //DEBUG_PRINT(("Cannot Install Keyboard"));
        return -1;
    }

    if(!al_install_mouse()){
        CRITICAL("Error: NO MOUSE FOR YOU");
        return -1;
    }

    if(!config_init()){
        char *root = get_file_path(nullptr, "config.ini");
        ALLEGRO_FILE * fp = al_fopen(root, "w");
        config_create_default(fp);
        al_fclose(fp);
        if(root) delete[] root;
    }







    //init_phyfs();


    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_install_mouse();
    al_init_acodec_addon();
    al_init_native_dialog_addon();

    /*
    if(window_conf.vsync <= 0){
        al_set_new_display_option(ALLEGRO_VSYNC,2, ALLEGRO_REQUIRE);
    }
    */

    /*
    if(window_conf.fullscreen <= 0){
        al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL_3_0 | ALLEGRO_RESIZABLE);
    }else {
        al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_OPENGL_3_0 | ALLEGRO_RESIZABLE);
    }
    */

    settings_t *settings = config_get();

    if(settings->fullscreen.b_field && settings->opengl.b_field){
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_FULLSCREEN);
    }else if(settings->opengl.b_field){
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    }




    al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR);


    g_display =  al_create_display(800, 600);

    int w,h;
    w = al_get_display_width(g_display);
    h = al_get_display_height(g_display);

    g_screen  =  al_create_bitmap(w,h);

    al_get_keyboard_state(&g_kbdstate);
    al_set_target_bitmap(g_screen);
    al_set_target_bitmap(al_get_backbuffer(g_display));


    g_timer = al_create_timer( (double) 1.0f / TICKSPERFRAME ); // main game timer updates every 1/60 secs (0.013 ms)
    g_time = al_create_timer(0.1); // 100 ms (to convert in seconds)
    g_queue = al_create_event_queue(); //create event queue


    al_register_event_source(g_queue, al_get_display_event_source(g_display));
    al_register_event_source(g_queue, al_get_keyboard_event_source());
    al_register_event_source(g_queue, al_get_mouse_event_source());
    al_register_event_source(g_queue, al_get_timer_event_source(g_timer));

    /* register the ingame time   when the game starts  the timing starts */
    al_register_event_source(g_queue, al_get_timer_event_source(g_time));

    al_set_window_title(g_display, "SHMUP MORE LIGHT!");
    al_start_timer(g_timer);
    al_start_timer(g_time);
    al_set_target_bitmap(al_get_backbuffer(g_display));
    return 0;
}

void window_init(void){
    // custom inits
    init_allegro();
    keyboard_start();
    mouse_init();
    init_path();
    mixer_init(2);

    if(!tiles_init()){
        CRITICAL("Error When tried to load spritesheet");
        is_window_open = false;

        return;
    }


    // start the editor essential variables;
    editor_init();


    /* init IMGUI */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();
    ImGui_ImplAllegro5_Init(get_window_display());

    is_window_open = true;
}

void window_close(void){
    //ImGui::DestroyContext();
    //ImGui_ImplAllegro5_Shutdown();


    editor_destroy();
    destroy_path();
    mixer_destroy();
    config_destroy();
    tiles_destroy();
    mouse_destroy();




    if (g_display != nullptr) al_destroy_display(g_display);
    if(g_queue    != nullptr) al_destroy_event_queue(g_queue);
    if(g_screen   != nullptr) al_destroy_bitmap(g_screen);
    if(g_timer    != nullptr) al_destroy_timer(g_timer);
    if(g_time     != nullptr) al_destroy_timer(g_time);
}

ALLEGRO_DISPLAY* get_window_display(void){
    return g_display;
}
ALLEGRO_EVENT_QUEUE* get_window_queue(void){
    return g_queue;
}
ALLEGRO_TIMER *get_window_timer(void){
    return g_timer;
}
ALLEGRO_TIMER *get_window_actual_time(void){
    return g_time;
}

bool window_open(void){
    return is_window_open;
}

void window_exit_loop(void){
    is_window_open = false;
}

int64_t get_window_time_ms(void){
    return timer_milliseconds;
}

ALLEGRO_BITMAP *get_window_screen(void){
    return g_screen;
}

void set_window_time_ms(int64_t time){
    timer_milliseconds = time;
}

void window_gracefully_quit(const std::string &msg){
    if(!issue_gracefully_close) issue_gracefully_close = true;
    if(is_window_open) window_exit_loop();  // finish the main loop isnt finished
    if(!msg.c_str()){
        LOG("---- GRACEFULLY QUITED: No Message ----\n\n");
    }

    LOG("---- GRACEFULLY QUITED: %s ----\n\n", msg.c_str());
    window_close();
}


bool window_request_gracefully_closing(void){
    return issue_gracefully_close;
}


int window_get_width(void){
    return al_get_display_width(g_display);
}
int window_get_height(void){
     return al_get_display_height(g_display);
}

void set_window_title(const std::string title)
{
    al_set_window_title(get_window_display(), title.c_str());
}
#endif
