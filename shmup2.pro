TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXX = g++

SOURCES += \
    src/fs.cpp \
    src/main.cpp \
    src/states/IGameState.cpp \
    src/CEngine.cpp \
    src/shared.cpp \
    src/window.cpp \
    src/keyboard.cpp \
    src/mouse.cpp \
    src/spaceship.cpp \
    src/mixer.cpp \
    src/level.cpp \
    src/menu.cpp \
    src/path.cpp \
    src/dir.cpp \
    src/render.cpp \
    src/tiles.cpp \
    src/config.cpp \
    src/editor.cpp \
    src/thread.cpp \
    src/text.cpp \
    src/particle.cpp \
    src/vector2.cpp \
    src/emitter.cpp \
    src/states/GameStateManager.cpp \
    src/gamestates/CMainGameState.cpp \
    src/gamestates/CMenuState.cpp \
    src/states/NonCopyable.cpp \
    src/states/NonMovable.cpp \
    src/Utils/CRandom.cpp \
    src/Utils/CRect.cpp \
    src/Utils/CText.cpp \
    lib/imgui/imgui_draw.cpp \
    lib/imgui/imgui.cpp \
    lib/imgui/imgui_widgets.cpp \
    src/GUI/imgui_impl_allegro5.cpp \
    src/gamestates/CEditorState.cpp \
    src/Utils/CUtils.cpp


HEADERS += \
    include/fs.h \
    include/window.h \
    include/states/IGameState.h \
    include/CEngine.h \
    include/shared.h \
    include/keyboard.h \
    include/mouse.h \
    include/spaceship.h \
    include/mixer.h \
    include/level.h \
    include/menu.h \
    include/path.h \
    include/dir.h \
    include/render.h \
    include/main.h \
    include/tiles.h \
    include/config.h \
    include/editor.h \
    include/thread.h \
    include/text.h \
    include/particle.h \
    include/vector2.h \
    include/emitter.h \
    include/states/GameStateManager.h \
    include/gamestates/CMainGameState.h \
    include/gamestates/CMenuState.h \
    include/states/NonCopyable.h \
    include/states/NonMovable.h \
    include/Utils/CRandom.h \
    include/Utils/CRect.h \
    include/Utils/CText.h \
    lib/imgui/imgui.h \
    include/GUI/imgui_impl_allegro5.h \
    include/gamestates/CEditorState.h \
    include/Utils/CUtils.h


QMAKE_CXXFLAGS_DEBUG += -std=c++17 -Wall -Wextra -fpermissive -Wpedantic -O0 -g
QMAKE_CXXFLAGS_RELEASE += -s -std=c++17 -Wall -Wextra -fpermissive -pedantic -Os


win32: {
    DEFINES += DEBUG_MODE

    INCLUDEPATH += include/
    DEPENDPATH  += include/


    INCLUDEPATH += lib/imgui/
    DEPENDPATH  += lib/imgui/


    INCLUDEPATH += D:\projetos\libs\liballegro-5.2.8-release\include
    LIBS += -LD:\projetos\libs\liballegro-5.2.8-release\lib
    LIBS += -lallegro \
            -lallegro_audio \
            -lallegro_acodec \
            -lallegro_font \
            -lallegro_ttf \
            -lallegro_image \
            -lallegro_dialog \
            -lallegro_primitives

}

unix: {

    INCLUDEPATH += include/
    DEPENDPATH  += include/

    INCLUDEPATH += lib/imgui
    DEPENDPATH  += lib/imgui

    INCLUDEPATH += -I/usr/local/include
    DEPENDPATH  += /usr/local/include
    LIBS += -L/usr/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives

    INCLUDEPATH += -I/usr/include/allegro5
    DEPENDPATH  += /usr/include/allegro5

    LIBS += -L/usr/lib64 -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives



}

macx: {

    INCLUDEPATH += include/
    DEPENDPATH  += include/

    LIBS += -L/usr/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives
    INCLUDEPATH += /usr/local/include
    DEPENDPATH  += /usr/local/include
}







