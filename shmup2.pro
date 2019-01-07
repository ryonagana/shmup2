TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    window.c \
    keyboard.c \
    spaceship.c


HEADERS += \
    window.h \
    keyboard.h \
    spaceship.h

win32: LIBS += -L$$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/lib/ -lliballegro-5.0.10-monolith-mt-debug

INCLUDEPATH += $$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/include
DEPENDPATH += $$PWD/../../libs/allegro-5.0.10-mingw-4.7.0/include
