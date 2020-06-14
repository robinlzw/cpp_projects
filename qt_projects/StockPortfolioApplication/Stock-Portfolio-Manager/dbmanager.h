/*
* dbmanager.h
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkRequest"
#include "QtNetwork/QNetworkReply"
#include "QUrl"
#include "QEventLoop"
#include "stock.h"
#include "stocklist.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QVariant>
#include <vector>
using std::vector;
#include <map>
using std::map;

typedef map<string, StockList> StockListMap;

class DbManager
{
private:
    unsigned userID;                // userID variable
    StockList stocks;                   // stock list object
    vector<Stock> stockVector;          // vector of stocks
    vector<string> nasdaqVector;        // nasdaq vector
    QSqlDatabase db;                    // variable for the database
    StockListMap stockLists;            // map of stock lists
    string url;                         // url for nasdaq
    StockList _loadStocks();    // loads the stocks from the database
    void _loadStockLists(unsigned);     // loads stock list


public:
    DbManager();                                                // constructor
    bool updateStock(const string &, double, double, int, double, int); // updates stock in db and local copy
    StockList &getStocks();                                 // returns stock map
    void addList(const string &, vector<string>);                    // adds a new list to the map of stock lists
    void removeList(QString);                               //removes a stocklist
    StockList* findList(const string &);
    void addStockToList(const string &);
    StockListMap &getStockLists();                         // get stock lists
    void setUserID(unsigned);                               // sets the userid
    vector<string> splitString(const string &, char);           // chops up nasdaq data
    void nasdaq();                                              // nasdaq method
    void loadData(unsigned);
    ~DbManager();                                               // Destructor
};

#endif // DBMANAGER_H
