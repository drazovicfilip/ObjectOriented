#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T23:26:07
#
#-------------------------------------------------

QT       += core gui
CONFIG += console
QMAKE_CFLAGS += -v

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PoolTable
TEMPLATE = app


SOURCES += main.cpp \
    dialog.cpp \
    poolgame.cpp \
    stageonetable.cpp \
    stageoneball.cpp \
    stageonefactory.cpp \
    gamebuilder.cpp \
    initializer.cpp \
    stagetwofactory.cpp \
    stagetwoball.cpp \
    stagetwotable.cpp \
    stagetwopocket.cpp \
    cueballdecorator.cpp

HEADERS  += dialog.h \
    poolgame.h \
    table.h \
    ball.h \
    stageonetable.h \
    stageoneball.h \
    abstractfactory.h \
    stageonefactory.h \
    gamebuilder.h \
    initializer.h \
    stagetwofactory.h \
    stagetwoball.h \
    stagetwotable.h \
    stagetwopocket.h \
    pocket.h \
    cueballdecorator.h

