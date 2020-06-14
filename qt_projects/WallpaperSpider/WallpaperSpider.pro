#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T14:41:36
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = WallpaperSpider
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += src/main.cpp \
    src/HttpGet.cpp \
    src/website/jj20.cpp \
    src/website/SpatialReference.cpp

HEADERS += \
    src/HttpGet.hpp \
    src/website/jj20.hpp \
    src/website/SpatialReference.hpp
