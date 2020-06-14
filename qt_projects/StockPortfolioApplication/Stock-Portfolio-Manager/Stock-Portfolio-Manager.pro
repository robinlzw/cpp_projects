#-------------------------------------------------
#
# Project created by QtCreator 2017-11-11T02:18:46
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Stock-Portfolio-Manager
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


SOURCES += \
        stockportfolioapp.cpp \
    stock.cpp \
    stocklist.cpp \
    dbmanager.cpp \
    stocktablemodel.cpp \
    newstocklistdialog.cpp \
    logindialog.cpp \
    user.cpp \
    usermanager.cpp \
    editlistdialog.cpp \
    main.cpp \
    stocklistmodel.cpp \
    addstockdialog.cpp

HEADERS += \
        stockportfolioapp.h \
    stock.h \
    stocklist.h \
    dbmanager.h \
    stocktablemodel.h \
    newstocklistdialog.h \
    logindialog.h \
    user.h \
    usermanager.h \
    editlistdialog.h \
    stocklistmodel.h \
    addstockdialog.h

FORMS += \
        stockportfolioapp.ui \
    newstocklistdialog.ui \
    logindialog.ui \
    editlistdialog.ui \
    addstockdialog.ui
