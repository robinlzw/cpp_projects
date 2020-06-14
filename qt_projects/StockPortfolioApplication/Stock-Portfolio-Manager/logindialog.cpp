/*
 * logindialog.cpp
 * Authors: Christian Kimball, Nicholas Hagan, Zachery Foresythe
 * Fall 2017
 * Course: CS245 - OOP w/ C++
 */

#include "logindialog.h"
#include "ui_logindialog.h"
#include "stockportfolioapp.h"
#include "ui_stockportfolioapp.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    passVerified = false;
    manager.initUser(this->getUsername(), this->getPassword());
}

unsigned LoginDialog::getUserID()
{
    return manager.getUser().getUserID();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

string LoginDialog::getUsername()
{
    return ui->usernameBox->text().toStdString();
}

string LoginDialog::getPassword()
{
    return ui->passwordBox->text().toStdString();
}

void LoginDialog::done(int result)
{
    if(QDialog::Accepted == result)
    {
        QString username = ui->usernameBox->text();
        QString password = ui->passwordBox->text();
        string un = username.toStdString();
        string pass = password.toStdString();
        //if the entered username and password are not empty
        if(!username.isEmpty() && !password.isEmpty())
        {
            //check for successfully matching login info
            if(manager.login(un, pass))
            {
                QDialog::done(result);
            }
            //login info does not match
            else
            {
                //display warning
                QMessageBox::warning(
                            this,
                            tr("Alert"),
                            tr("Invalid Login"));
                ui->passwordBox->clear();
                ui->usernameBox->setFocus();
            }
        }
        //some field is left blank
        else
        {
            QMessageBox::warning(
                        this,
                        tr("Alert"),
                        tr("Fields cannot be blank"));
            ui->passwordBox->clear();
            ui->passwordBox->setFocus();
        }
    }
    //cancel, close or esc was pressed
    else
    {
        QDialog::done(result);
    }
}

/*
 * Sets whether password was verified
 */
void LoginDialog::setPassVerified(bool ver)
{
    passVerified = ver;
}

/*
 * Gets whether password was verified
 */
bool LoginDialog::getPassVerified()
{
    return passVerified;
}
