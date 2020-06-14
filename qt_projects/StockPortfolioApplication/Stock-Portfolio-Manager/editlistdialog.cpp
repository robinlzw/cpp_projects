#include "editlistdialog.h"
#include "ui_editlistdialog.h"

EditListDialog::EditListDialog(StockList &stocks, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditListDialog)
{
    ui->setupUi(this);

    listModel = new StockListModel(stocks);

    ui->stockListView->setModel(listModel);

    ui->stockListView->setCurrentIndex(this->listModel->index(0,0));


}

EditListDialog::~EditListDialog()
{
    delete listModel;
    delete ui;
}
