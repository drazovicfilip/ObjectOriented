#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T23:26:07
#
#-------------------------------------------------

QT       += core gui
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PoolTable
TEMPLATE = app


SOURCES += main.cpp \
    dialog.cpp \
    poolgame.cpp \
    stageonetable.cpp \
    stageonefactory.cpp \
    gamebuilder.cpp \
    initializer.cpp \
    stagetwofactory.cpp \
    stagetwotable.cpp \
    stagetwopocket.cpp \
    balldecorator.cpp \
    simpleball.cpp \
    compositeball.cpp

HEADERS  += dialog.h \
    poolgame.h \
    table.h \
    ball.h \
    stageonetable.h \
    abstractfactory.h \
    stageonefactory.h \
    gamebuilder.h \
    initializer.h \
    stagetwofactory.h \
    stagetwotable.h \
    stagetwopocket.h \
    pocket.h \
    balldecorator.h \
    simpleball.h \
    compositeball.h

