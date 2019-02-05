TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CC=gcc #change to mingw-w64-gcc ?
QMAKE_CFLAGS=-std=c11

SOURCES += \
    src/main.c \
    src/window.c \
    src/keyboard.c \
    src/mouse.c \
    src/spaceship.c \
    src/mixer.c \
    src/shared.c \
    src/level.c \
    src/path.c \
    src/render.c \
    src/tiles.c \
    src/config.c \
    src/editor.c \
    src/thread.c \
    src/text.c


HEADERS += \
    include/window.h \
    include/keyboard.h \
    include/mouse.h \
    include/spaceship.h \
    include/mixer.h \
    include/shared.h \
    include/level.h \
    include/path.h \
    include/render.h \
    include/main.h \
    include/tiles.h \
    include/config.h \
    include/editor.h \
    include/thread.h \
    include/text.h

win32: {

    INCLUDEPATH += include/
    DEPENDPATH  += include/

    DEFINES += ALLEGRO_STATICLINK
    LIBS += -L$$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/lib/ -lallegro-5.0.10-monolith-static-mt-debug  -lFLAC-1.2.1-static-mt-debug -ldumb-0.9.3-static-mt-debug -lvorbisfile-1.3.2-static-mt-debug -lvorbis-1.3.2-static-mt-debug  -lfreetype-2.4.8-static-mt-debug  -logg-1.2.1-static-mt-debug -lzlib-1.2.5-static-mt-debug -lopenal-1.14-static-mt-debug  -lzlib-1.2.5-static-mt-debug    -lm -lgdiplus -luuid -lkernel32 -lwinmm -lpsapi -lopengl32 -lglu32 -luser32 -lcomdlg32 -lgdi32 -lshell32 -lole32 -ladvapi32 -lws2_32 -lshlwapi
    INCLUDEPATH += $$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/include
    DEPENDPATH += $$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/include

    LIBS += -L$$PWD/../libs/allegro-5.0.10-mingw-4.7.0/lib/ -lallegro-5.0.10-monolith-static-mt-debug  -lFLAC-1.2.1-static-mt-debug -ldumb-0.9.3-static-mt-debug -lvorbisfile-1.3.2-static-mt-debug -lvorbis-1.3.2-static-mt-debug  -lfreetype-2.4.8-static-mt-debug  -logg-1.2.1-static-mt-debug -lzlib-1.2.5-static-mt-debug -lopenal-1.14-static-mt-debug  -lzlib-1.2.5-static-mt-debug    -lm -lgdiplus -luuid -lkernel32 -lwinmm -lpsapi -lopengl32 -lglu32 -luser32 -lcomdlg32 -lgdi32 -lshell32 -lole32 -ladvapi32 -lws2_32 -lshlwapi
    INCLUDEPATH += $$PWD/../libs/allegro-5.0.10-mingw-4.7.0/include
    DEPENDPATH += $$PWD/../libs/allegro-5.0.10-mingw-4.7.0/include


}

unix: {
    LIBS += -L/usr/lib -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives
    INCLUDEPATH += /usr/include
    DEPENDPATH  += /usr/include
}


