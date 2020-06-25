//#include "mainwindow.h"
#include <QApplication>
#include "ImageWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageWidget w;
    QImage img("test.jpg");
    w.setImageWithData(img);
    w.show();
    return a.exec();
}
