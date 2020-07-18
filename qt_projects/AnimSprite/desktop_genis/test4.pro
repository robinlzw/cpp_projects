#-------------------------------------------------
#
# Project created by QtCreator 2020-07-17T21:12:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += texttospeech

TARGET = test4
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        MyXcbEventFilter.cpp \
        evle.cpp \
        globalapplication.cpp \
        main.cpp

HEADERS += \
        MyXcbEventFilter.h \
        evle.h \
        globalapplication.h

FORMS += \
        evle.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resources/1.png \
    Resources/2.png \
    Resources/3.png \
    Resources/4.png \
    Resources/4_2.png \
    Resources/5.png \
    Resources/6.png \
    Resources/7.png \
    Resources/8.png \
    Resources/anniu.png \
    Resources/icon.png \
    Resources/lazy.png \
    Resources/shime10.png \
    Resources/shime11.png \
    Resources/shime13.png \
    Resources/shime14.png \
    Resources/shime15.png \
    Resources/shime16.png \
    Resources/shime17.png \
    Resources/shime18.png \
    Resources/shime19.png \
    Resources/shime2.png \
    Resources/shime21.png \
    Resources/shime24.png \
    Resources/shime25.png \
    Resources/shime26.png \
    Resources/shime27.png \
    Resources/shime28.png \
    Resources/shime29.png \
    Resources/shime3.png \
    Resources/shime30.png \
    Resources/shime31.png \
    Resources/shime32.png \
    Resources/shime33.png \
    Resources/shime34.png \
    Resources/shime35.png \
    Resources/shime36.png \
    Resources/shime37.png \
    Resources/shime38.png \
    Resources/shime39.png \
    Resources/shime40.png \
    Resources/shime41.png \
    Resources/shime42.png \
    Resources/shime43.png \
    Resources/shime44.png \
    Resources/shime45.png \
    Resources/shime46.png \
    Resources/shime7.png \
    Resources/shime8.png \
    Resources/shime9.png \
    Resources/xuenai.png
