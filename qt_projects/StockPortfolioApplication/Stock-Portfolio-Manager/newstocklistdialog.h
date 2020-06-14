/*
* newstocklistdialog.h
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#ifndef NEWSTOCKLISTDIALOG_H
#define NEWSTOCKLISTDIALOG_H

#include <QDialog>
#include <vector>
using std::vector;
#include <string>
using std::string;

namespace Ui {
class NewStockListDialog;
}

class NewStockListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewStockListDialog(QWidget *parent = 0);   // constructor
    string getStockListName();                          // gets stock list name from dialog
    vector<string> getTickersToAdd();                   // gets the tickers to add from dialog, stores them in vector
    vector<string> splitString(const string &, char);           // chops up  data
    ~NewStockListDialog();                              // destructor

private:
    Ui::NewStockListDialog *ui;
    vector<string> listOfTickers;                       // vector of the tickers
    void virtual done(int);                             // overrides done function
};

#endif // NEWSTOCKLISTDIALOG_H
