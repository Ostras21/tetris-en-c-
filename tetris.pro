QT -= gui
QT -= core

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = tetris
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/board.cpp \
    src/piece.cpp \
    src/game.cpp \
    src/display.cpp

HEADERS += \
    src/board.h \
    src/piece.h \
    src/game.h \
    src/display.h
