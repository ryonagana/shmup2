TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    window.c \
    keyboard.c \
    spaceship.c \
    mixer.c \
    shared.c \
    level.c \
    path.c


HEADERS += \
    window.h \
    keyboard.h \
    spaceship.h \
    mixer.h \
    shared.h \
    level.h \
    path.h

win32: LIBS += -L$$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/lib/ -lliballegro-5.0.10-monolith-mt-debug

INCLUDEPATH += $$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/include
DEPENDPATH += $$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/include
