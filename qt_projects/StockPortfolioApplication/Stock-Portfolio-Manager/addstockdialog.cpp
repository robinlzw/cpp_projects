#include "addstockdialog.h"
#include "ui_addstockdialog.h"

AddStockDialog::AddStockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStockDialog)
{
    ui->setupUi(this);
}

AddStockDialog::~AddStockDialog()
{
    delete ui;
}

void AddStockDialog::on_buttonBox_accepted()
{

}
