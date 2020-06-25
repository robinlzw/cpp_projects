/*
* stockportfolioapp.cpp
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#include "ui_stockportfolioapp.h"
#include "stockportfolioapp.h"
#include "newstocklistdialog.h"
#include "editlistdialog.h"
#include "logindialog.h"
#include "dbmanager.h"
#include <iterator>
using std::iterator;

/*
 * Constructor
 */
stockportfolioapp::stockportfolioapp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stockportfolioapp)
{
    ui->setupUi(this);

}

/*
 * Loads data
 */
void stockportfolioapp::loadData(unsigned uID)
{
    dbm.loadData(uID);
}

/*
 * Initializes GUI
 */
void stockportfolioapp::initGUI()
{
    // create new stock model and abbly it to the table view
    model = new StockTableModel(dbm.getStocks(), this);
    ui->stockTableView->setModel(model);

    // set table view to allow the columns to expand
    ui->stockTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // stretch the columns headers to fit the width of the table view
    ui->stockTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // resize the columns
    ui->stockTableView->resizeColumnsToContents();

    // sets message timer
    this->setMessageTimer();

    this->addToCombo();
}

/*
 * Destructor
 */
stockportfolioapp::~stockportfolioapp()
{
    delete model;
    delete messageTimer;
    delete ui;
}

/*
 * Sets the message timer
 */
void stockportfolioapp::setMessageTimer()
{
    messageTimer = new QTimer(this);
    messageTimer->setInterval(3000);    // 3 seconds
    connect(messageTimer, SIGNAL(timeout()), this, SLOT(on_setTimer()));
    messageTimer->start();
}

/*
 * Every three seconds update stocks
 */
void stockportfolioapp::on_setTimer()
{

}

/*
 * Opens the dialog for adding a new stock list
 */
void stockportfolioapp::openNewStockListDialog()
{
    // create new dialog window object
    NewStockListDialog nsld(this);

    // sets modal to true, disabled while open
    nsld.setModal(true);

    // if window successfully launches...
    if (nsld.exec() == QDialog::Accepted)
    {
        // gets stock list info
        string name = nsld.getStockListName();
        vector<string> ticks = nsld.getTickersToAdd();

        // adds stock list info
        dbm.addList(name, ticks);

        // adds to combo box
        this->addToCombo();

        // creates index
        int index = ui->stockListBox->findText(QString::fromStdString(name));

        // if text was found...
        if (index != -1)
        {
            // set index
            ui->stockListBox->setCurrentIndex(index);
        }
    }
}


/*
 * Opens new stock list dialog from menu
 */
void stockportfolioapp::on_actionNew_triggered()
{
    this->openNewStockListDialog();
}

/*
 * Opens new stock list dialog when button clicked
 */
void stockportfolioapp::on_newListButton_clicked()
{
    this->openNewStockListDialog();
}

/*
 * opens the dialog for editing a stocklist
 */
void stockportfolioapp::openEditListDialog()
{
    // create new dialog window object
    EditListDialog eld(dbm.getStocks(), this);

    // sets modal to true, disabled while open
    eld.setModal(true);

    // if window successfully launches...
    if (eld.exec() == QDialog::Accepted)
    {

    }
}

/*
 * opens the edit stock list
 */
void stockportfolioapp::on_editListButton_clicked()
{
    this->openEditListDialog();
}

/*
 * opens the edit stock list dialog menu
 */
void stockportfolioapp::on_actionEdit_triggered()
{
    this->openEditListDialog();
}

void stockportfolioapp::on_removeListButton_clicked()
{
    QString listName = ui->stockListBox->currentText();

    dbm.removeList(listName);
}

/*
 * adds stock list name to combo
 */
void stockportfolioapp::addToCombo()
{
    QStringList stockListNames;

    StockListMap lists = dbm.getStockLists();

    for (auto &sl : lists)
    {
        string stockListName = sl.first;
        stockListNames << QString::fromStdString(stockListName);
    }

    ui->stockListBox->clear();
    ui->stockListBox->addItems(stockListNames);
}
