#ifndef ADDSTOCKDIALOG_H
#define ADDSTOCKDIALOG_H

#include <QDialog>

namespace Ui {
class AddStockDialog;
}

class AddStockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStockDialog(QWidget *parent = 0);
    ~AddStockDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddStockDialog *ui;
};

#endif // ADDSTOCKDIALOG_H
