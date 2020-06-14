/*
* main.cpp
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#include "stockportfolioapp.h"
#include "usermanager.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    stockportfolioapp w;

    //LoginDialog loginD;

    // if window successfully launches...
    //if (loginD.exec() == QDialog::Accepted)
    {
        //unsigned uID = loginD.getUserID();
        unsigned uID = 11;
        w.loadData(uID);
        w.initGUI();
        w.show();
    }

    return a.exec();
}
