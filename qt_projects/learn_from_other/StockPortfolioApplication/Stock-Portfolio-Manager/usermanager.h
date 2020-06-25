/*
 * usermanager.h
 * Authors: Christian Kimball, Nicholas Hagan, Zachery Foresythe
 * Fall 2017
 * Course: CS245 - OOP w/ C++
 */

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user.h"
#include "dbmanager.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QVariant>

class UserManager
{
public:
    //Constructors
    UserManager();                                      // Default constructor
    //UserManager(const string &, const string &);        //Two parameter constructor
    ~UserManager();                                     //Destructor

    //Getter
    User getUser(){ return user; }                        //returns the user object that is being managed

    //Helper Functions
    void registerUser(User);                            //register a user to the system
    bool login(const string &, const string &);                                       //log the user into the system
    void initUser(const string &, const string &);      // initializes user data member

private:
    User user;                                          // user
    QSqlDatabase db;                                    // variable for the database
    string _hashPassword(const string &);               //hash the password of the user
    bool _usernameCheck(const string &);                // checks username
    bool _passCheck(const string &);                    // checks pass
};

#endif // USERMANAGER_H
