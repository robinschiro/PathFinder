#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T11:08:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathFinder
TEMPLATE = app


SOURCES +=  src/main.cpp\
            src/mainwindow.cpp \
            src/renderarea.cpp \

HEADERS  += inc/mainwindow.h \
            inc/renderarea.h \

FORMS    += mainwindow.ui

DISTFILES += \
    build/PathFinder \
    README.md
