#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T11:08:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -O0 -std=c++11

TARGET = PathFinder
TEMPLATE = app


SOURCES +=  src/main.cpp\
            src/mainwindow.cpp \
            src/RenderArea.cpp \
            src/PathVisualizer.cpp \
            src/VoronoiGenerator.cpp \
            src/RenderLayer.cpp \
            src/RefinedVoronoiDiagram.cpp \
            src/SearchableGraph.cpp \
    src/RenderAreaWidget.cpp

HEADERS  += inc/mainwindow.h \
            inc/RenderArea.h \
            inc/PathVisualizer.h \
            inc/VoronoiGenerator.h \
            inc/voronoi_visual_utils.hpp \
            inc/RenderLayer.h \
            inc/RefinedVoronoiDiagram.h \
            inc/SearchableGraph.h \
            inc/GeometryStructures.h \
            inc/Util.h \
    inc/RenderAreaWidget.h

INCLUDEPATH += /home/robin/boost_1_60_0 \
               $$_PRO_FILE_PWD_/inc

FORMS    += mainwindow.ui

DISTFILES += \
    build/PathFinder \
    README.md
