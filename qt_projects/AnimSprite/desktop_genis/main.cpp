//#include "evle.h"
//#include <QtWidgets/QApplication>
//#include "globalapplication.h"
//#include "MyXcbEventFilter.h"

//int main(int argc, char *argv[])
//{
//    // QApplication app(argc, argv);
//    GlobalApplication app(argc, argv);

//    evle w;
//    //a.setWindowInstance(&w);
//    w.show();

//    MyXcbEventFilter m_MainWindow(1);
//    app.installNativeEventFilter(&m_MainWindow);
//    return app.exec();
//}

#include <QMainWindow>
#include <QApplication>
#include <QAbstractNativeEventFilter>
#include "globalapplication.h"
#include "evle.h"
#include <windows.h>

//class MyAppNativeEventFilter  : public QAbstractNativeEventFilter
//{
//    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
//};

//bool MyAppNativeEventFilter::nativeEventFilter(const QByteArray & eventType, void * message, long * result) {

//    MSG * pMsg = reinterpret_cast<MSG *>(message);
//    qDebug() << pMsg->message;

//    return false;
//}


//int main(int argc,   char* argv [])
//{
//    QApplication app(argc, argv);
//    MyAppNativeEventFilter filter;
//    app.installNativeEventFilter(&filter);
//    evle w;
//    w.show();
//    return app.exec();
//}


class MainWindow  : public QMainWindow, public QAbstractNativeEventFilter
{
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
};

bool MainWindow::nativeEventFilter(const QByteArray & eventType, void * message, long * result) {

    MSG * pMsg = reinterpret_cast<MSG *>(message);
    qDebug() << pMsg->message;

    return false;
}

int main(int argc,   char* argv [])
{
    QApplication app(argc, argv);
    MainWindow filter;
    evle w;
    w.show();
    app.installNativeEventFilter(&filter);
    return app.exec();
}
