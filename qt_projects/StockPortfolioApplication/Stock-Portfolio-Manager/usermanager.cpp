/*
 * usermanager.cpp
 * Authors: Christian Kimball, Nicholas Hagan, Zachery Foresythe
 * Fall 2017
 * Course: CS245 - OOP w/ C++
 */

#include "usermanager.h"
#include <QCryptographicHash>
#include <exception>
#include <iostream>
using std::cout; using std::endl;

/*
 * Default constructor
 */
UserManager::UserManager()
{
    //create Database connection object
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={ODBC Driver 13 for SQL Server};Server=tcp:portfolio-svr.database.windows.net,1433;Database=StockPortfolioDB;Uid=cs245;Pwd=Thomas123;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;");

}



/*
 * Destructor
 * Closes Database connection
 * Removes variables from memory
 */
UserManager::~UserManager()
{
    db.close();
}

/*
 * Hashes the password of the user
 * Uses SHA3 224 Standard
 */
string UserManager::_hashPassword(const string &pass)
{
    //Using SHA3 224 Standard
    QString hashPass = QString(QCryptographicHash::hash((pass.c_str()), QCryptographicHash::Sha3_224).toHex());
    //return the hashed password
    return hashPass.toStdString();
}

/*
 * Registers a new user to the System
 * Adds it's data to the user table in the database
 * Currently not implented
 */
void UserManager::registerUser(User newUser)
{

}

/*
 * Used to log in the user
 * Checks hashed password with what is in the database
 * Returns true if the hashes match
 * Else returns false
 */
bool UserManager::login(const string &un, const string &pass)
{
    QVariant username = QString::fromStdString(un);

    string hashedPass = this->_hashPassword(pass);

    // opens database connection
    bool ok = db.open();

    // if the database connection is successful...
    if(ok)
    {
         // creates a query that can only be read forward
         QSqlQuery query;
         query.setForwardOnly(true);

         QString sql = "SELECT userID, password FROM [User] WHERE username = ?";

         // create prepared statement
         //gets password from User table where the username is that of the user object
         query.prepare(sql);

         //bind the value of username
         query.bindValue(0, username);

         //execute SQL query
         if(query.exec())
         {
             // while there are still more records in the result set
             while(query.next())
             {
                 //store data in local variables
                 unsigned uID = query.value(0).toUInt();
                 string pw = query.value(1).toString().toStdString();

                 //if the hashed password entered by the user matches the one in the Database for the given username
                 if(hashedPass == pw)
                 {
                     user.setUserID(uID);
                     //set the ID of the user and return
                     return true;
                 }
                 //if they do not, exit
                 else
                 {
                     return false;
                 }
             }

        }
    }
    // if connection is not successful...
    else
    {
        // informs user there were connection issues
        cout << "There were issues connecting..." << endl;
    }

    //Database
    return false;
}

/*
 * Initializes user data members
 */
void UserManager::initUser(const string &name, const string &pass)
{
    user.setUsername(name);
    user.setPassHash(pass);
}

///*
// * checks username
// */
//bool UserManager::_usernameCheck(const string &name)
//{
//    //requirements flag variables
//    bool hasUpper = false;
//    bool hasLower = false;
//    bool hasDigit = false;
//    bool hasSpecial = false;

//    //usernames must be b/w 6-16 characters long
//    if((name.length() < 6) || (name.length() > 16))
//    {
//        throw std::length_error("Username must be between 6-16 characters long");
//    }

//    //loop through the username to check for requirments
//    for(char c : name)
//    {
//        //check for uppercase
//        if(isupper(c))
//        {
//            hasUpper = true;
//        }

//        //check for lowercase
//        if(islower(c))
//        {
//            hasLower = true;
//        }

//        //check for digit
//        if(isdigit(c))
//        {
//            hasDigit = true;
//        }

//        //check for special characters
//        if(!isalnum(c))
//        {
//            hasSpecial = true;
//        }
//    }

//    //usernames must contain at least 1 uppercase character
//    if(hasUpper == false)
//    {
//        throw std::invalid_argument("Username must contain at least 1 uppercase letter");
//    }

//    //usernames must contain at least 1 lowercase character
//    if(hasLower == false)
//    {
//        throw std::invalid_argument("Username must contain at least 1 lower case letter");
//    }

//    //usernames must contain at least 1 digit
//    if(hasDigit == false)
//    {
//        throw std::invalid_argument("Username must contain at least 1 digit");
//    }

//    //usernames may not contain special characters
//    if(hasSpecial == true)
//    {
//        throw std::invalid_argument("Username may not contain any special characters");
//    }

//    if (hasUpper == true && hasLower == true && hasDigit == true && hasSpecial == false)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}

//bool UserManager::_passCheck(const string &pass)
//{
//    if(pass.empty())
//    {
//        throw std::invalid_argument("Hashed Password may not be blank");
//        return false;
//    }
//    return true;
//}
