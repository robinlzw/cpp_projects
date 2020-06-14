#include <QCoreApplication>

#include "HttpGet.hpp"

#include "website/jj20.hpp"

#include "website/SpatialReference.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HttpGet g;
    //g.saveFile(QUrl("http://tu1.desk.orsoon.com/1366x768/1605/9-160524160G8.jpg"),
    //           ".");
    //g.saveFile(QUrl("http://tu1.desk.orsoon.com/1440x900/1605/9-160524160G8.jpg"),
    //           "123");


    // jj20壁纸抓取
    //mainFormJJ20(&g);

    mainFormSpatialReference(&g);

    return a.exec();
}
