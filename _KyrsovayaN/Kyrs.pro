#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T00:40:55
#
#-------------------------------------------------

QT       += core gui

QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
    gamewidget.cpp \
    element.cpp \
    button.cpp \
    singleton.cpp \
    tetris.cpp \
    setimage.cpp \
    bonusbutton.cpp \
    records.cpp

HEADERS  += \
    gamewidget.h \
    element.h \
    button.h \
    singleton.h \
    tetris.h \
    setimage.h \
    bonusbutton.h \
    records.h

RESOURCES += \
    image.qrc
