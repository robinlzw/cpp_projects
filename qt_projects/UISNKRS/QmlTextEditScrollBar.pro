#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    fileio.cpp \
    poewr_key.cpp

RESOURCES += qml.qrc

DISTFILES +=

HEADERS += \
    fileio.h \
    poewr_key.h


INCLUDEPATH += C:/Users/lenovo/Downloads/vcpkg-master/installed/x64-windows/include .
LIBS        += C:/Users/lenovo/Downloads/vcpkg-master/installed/x64-windows/lib/jsoncpp.lib
