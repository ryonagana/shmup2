#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <cstdio>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_native_dialog.h>


class GameWindow {
public:

    enum RenderType {
        OPENGL,
        OPENGL_NEW,
        DIRECT3D
    };

    static constexpr double FPS = 60.0;
    static constexpr double DESIRED_FPS = 1.0/FPS;




    static GameWindow& getInstance(){
        static GameWindow s_gamewindow;
        return s_gamewindow;
    }

    GameWindow();
    int allegroInit(void);
    void setRender(int type);
    int createDisplay(int width, int height, bool fullscreen, bool vsync, double fps, int render_type,  const std::string& window_title, int flags);
    void Destroy();
    void Quit(const std::string& message = "Quit Successful");

    int getWidth(void) { return al_get_display_width(m_display); }
    int getHeight(void){ return al_get_display_height(m_display); }

    ALLEGRO_EVENT_QUEUE* getQueue(void) { return m_queue; }
    ALLEGRO_TIMER* getTimer(void) { return m_timer; }
    ALLEGRO_DISPLAY* getDisplay(void) { return m_display; }
    ALLEGRO_BITMAP *getScreenBuffer(void){ return m_screen; }
    ALLEGRO_FONT *getDebugFont() { return m_debug_font; }
    bool isWindowOpen(){ return m_is_running;  }
    void setWindow(bool val) {  m_window_started = val;  }

private:
    ALLEGRO_FONT *m_debug_font;
    int  m_width;
    int  m_height;
    std::string m_window_title;
    bool m_fullscreen;
    bool m_vsync;
    int m_render_flags;
    bool m_window_started;
    bool m_is_running;

    bool m_is_destroyed;


protected:
    ALLEGRO_EVENT_QUEUE *m_queue = nullptr;
    ALLEGRO_DISPLAY *m_display = nullptr;
     ALLEGRO_BITMAP *m_screen = nullptr;
    ALLEGRO_TIMER *m_timer = nullptr;
};




#endif
