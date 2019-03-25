#include "main.h"
#include "mouse.h"
#include "editor.h"
#include "config.h"
#include "menu.h"
#include "dir.h"
#include "CEngine.h"
#include "imgui.h"
#include "GUI/imgui_impl_allegro5.h"


int main(int  argc, char *argv[])
{
    UNUSED_PARAM(argc);
    UNUSED_PARAM(argv);

    srand(static_cast<unsigned int>(std::time(nullptr)));
    window_init();
    bool redraw = false;
    CEngine mainEngine;

    //mainEngine.Start();

    // main allegro event
    ALLEGRO_EVENT ev;

    while(window_open()){

        ALLEGRO_TIMEOUT timeout;

        al_init_timeout(&timeout, 0.6);
        al_wait_for_event_until(get_window_queue(), &ev, &timeout);


            switch(ev.type){

                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    mainEngine.setState(GameStateID::Menu);
                break;


                case ALLEGRO_EVENT_TIMER:
                {
                    if(ev.timer.source == get_window_timer()){
                        mainEngine.getState()->Update(&ev);
                        redraw = true;
                    }

                    if(ev.timer.source == get_window_actual_time()){

                    }
                    break;
                }
            }

         mainEngine.getState()->HandleInput(&ev);

        if(redraw && al_event_queue_is_empty(get_window_queue())){
            redraw = false;
            mainEngine.getState()->Draw();
            al_flip_display();

        }

    }
    mainEngine.getStateManager().DestroyAllStates();
    window_gracefully_quit("End of Main Loop");

    return 0;

}



