#include "mainwindow.h"
#include <QApplication>
#include <qt_windows.h>
#include "MyGlobalShortCut.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	//注册快捷键
	MyGlobalShortCut *shortcut = new MyGlobalShortCut("Ctrl+F9", &w);
	//绑定响应热键的slot
	QObject::connect(shortcut, SIGNAL(activated()), &w, SLOT(activated()));
	
	w.show();
	return a.exec();
}
