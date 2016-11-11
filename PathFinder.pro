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
            src/PathVisualizer.cpp \
            src/VoronoiGenerator.cpp

HEADERS  += inc/mainwindow.h \
            inc/renderarea.h \
            inc/PathVisualizer.h \
            inc/VoronoiGenerator.h \
            inc/voronoi_visual_utils.hpp

INCLUDEPATH += /home/robin/boost_1_60_0

FORMS    += mainwindow.ui

DISTFILES += \
    build/PathFinder \
    README.md
