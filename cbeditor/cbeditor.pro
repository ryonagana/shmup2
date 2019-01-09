#-------------------------------------------------
#
# Project created by QtCreator 2019-01-09T12:37:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cbeditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        cbeditormain.cpp \ 
       render.cpp \
       levelmap.cpp \
        ../tiles.c \
        ../level.c \
        ../path.c \
        ../shared.c \


HEADERS += \
        cbeditormain.h \
        ../tiles.h \
        ../level.h \
        ../path.h \
        ../shared.h \
    render.h \
    levelmap.h

FORMS += \
        cbeditormain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#only reason to add allegro as dependencies because my levels uses allegro internals like (ALLEGRO_FILE, ALLEGRO_PATH)
#to access in my editor i need to include
win32: {
    LIBS += -L$$PWD/../../../libs/allegro-5.0.10-mingw-4.7.0/lib/ -lallegro-5.0.10-monolith-mt
    INCLUDEPATH += $$PWD/../../../libs/allegro-5.0.10-mingw-4.7.0/include
    DEPENDPATH += $$PWD/../../../libs/allegro-5.0.10-mingw-4.7.0/include
}
