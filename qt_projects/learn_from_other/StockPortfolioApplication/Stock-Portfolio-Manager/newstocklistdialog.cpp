/*
* newstocklistdialog.h
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#include "newstocklistdialog.h"
#include "ui_newstocklistdialog.h"
#include <QMessageBox>
#include <string>
#include <sstream>
using std::istringstream;

NewStockListDialog::NewStockListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewStockListDialog)
{
    ui->setupUi(this);
}

string NewStockListDialog::getStockListName()
{
    return ui->stockListNameBox->text().toStdString();
}

/*
 * Overrides the done() method
 */
void NewStockListDialog::done(int result)
{
    // ok was pressed
    if(QDialog::Accepted == result)
    {
        // get the data entered by user
        QString stockListName = ui->stockListNameBox->text();
        QString ticks = ui->tickersAddBox->text();

        // if stock list name is not empty...
        if (!stockListName.isEmpty())
        {
            // calls done dialog
            QDialog::done(result);
        }
        // if it is empty...
        else if (stockListName.isEmpty())
        {
            // warns user that box is empty
            QMessageBox::warning(this, tr("Alert"), tr("Cannot leave fields empty."));
            // sets focus
            ui->stockListNameBox->setFocus();
        }
    }
    else
    {
        QDialog::done(result);
    }
    return;
}

/*
 * Gets the tickers to add from UI
 */
vector<string> NewStockListDialog::getTickersToAdd()
{
    string tickers = ui->tickersAddBox->text().toStdString();

    vector<string> newTickers = splitString(tickers, ' ');

    return newTickers;
}

 /*
  * Chops up a string by whitespace, stores it to vector
  */
vector<string> NewStockListDialog::splitString(const string &text, char sep)
{
    // creates field string, and fields vector data memebers
    string field;
    vector<string> fields;

    // creates an istringstream object that uses text paramter as a parameter
    istringstream inputStr(text);

    // while it can still get a line, adds field to fields vector
    while (getline(inputStr, field, sep))
    {
        fields.push_back(field);
    }

    // returns field vector
    return fields;
}


NewStockListDialog::~NewStockListDialog()
{
    delete ui;
}
