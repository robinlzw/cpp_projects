#pragma once
#ifndef EVLE_H
#define EVLE_H

#include <QtWidgets/QWidget>
#include <qpixmap.h>
#include <qmouseeventtransition.h>
#include <qpoint.h>
#include <qdesktopservices.h>
#include <qurl.h>
#include <QtGui/qevent.h>
#include <qdebug.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmenu.h>
#include <qpropertyanimation.h>
#include <qdesktopwidget.h>
#include <qpainter.h>
#include <qbitmap.h>
#include <windows.h>
#include <QtTextToSpeech\qtexttospeech.h>
#include <string>
#include <qaction.h>
#include <qmenu.h>
#include <qcursor.h>
#include <qtextcodec.h>
#include <qdialog.h>
#include <qmessagebox.h>
#include <qapplication.h>
using namespace std;
class evle : public QWidget
{
    Q_OBJECT

public:
    evle(QWidget *parent = Q_NULLPTR);
    ~evle();
private:
    QLabel* label;
    QPoint relativePos;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void leaveEvent(QEvent*);
    void enterEvent(QEvent*);
    void speak();
private slots:
    void about_window();
};

#endif
