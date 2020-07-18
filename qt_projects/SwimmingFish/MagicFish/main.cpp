#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qt_windows.h>
#include <QWindow>
#include "magicpool.h"
#include "MyGlobalShortCut.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<MagicPool>("an.utility", 1, 0, "MagicPool");
    qmlRegisterType<MagicPool>("MyGlobalShortCut", 1, 0, "MyGlobalShortCut");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    QObject* m_rootObject = engine.rootObjects().first();
    if(m_rootObject) {
        QWindow *window = qobject_cast<QWindow *>(m_rootObject);
        MyGlobalShortCut *shortcut = new MyGlobalShortCut("ESC", window);
        QObject::connect(shortcut, SIGNAL(activated()), window, SLOT(receiveActivated()));

        if(window) {
         //WId wid = window->winId();
         HWND winHandle=(HWND)window->winId();
             ShowWindow(winHandle, SW_HIDE);
             SetWindowLong(winHandle, GWL_EXSTYLE, GetWindowLong(winHandle, GWL_EXSTYLE)
                 | WS_EX_TRANSPARENT | WS_EX_LAYERED);
             ShowWindow(winHandle, SW_SHOW);
        }
    }



    return app.exec();
}
