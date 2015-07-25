#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T16:26:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Battleship
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    Square.cpp \
    SquareBoard.cpp \
    Button.cpp \
    Ship.cpp \
    Player.cpp \
    Computer.cpp \
    Human.cpp

HEADERS  += \
    Game.h \
    Square.h \
    SquareBoard.h \
    Button.h \
    Ship.h \
    Player.h \
    Computer.h \
    Human.h

FORMS    +=

DISTFILES +=

RESOURCES += \
    images.qrc
