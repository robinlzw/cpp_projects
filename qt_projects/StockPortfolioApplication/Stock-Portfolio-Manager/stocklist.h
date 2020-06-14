/*
* stocklist.h
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#ifndef STOCKLIST_H
#define STOCKLIST_H

#include "stock.h"
#include <string>
using std::string;
#include <map>
using std::map;

typedef map<string, Stock> StockMap;

class StockList
{

private:
    string stockListName;   // stores a name of the stock list
    StockMap stocks;        // stores a map of Stock objects
    unsigned stockListID;

public:
    StockList();                            // default constructor
    StockList(const string &);              // one parameter constructor

    void addToMap(Stock);                   // adds a stock to the map
    void removeFromMap(Stock);              // removes a stock from the map
    Stock *findStock(const string &);       // finds and returns the stock

    unsigned getStockListID();
    void setStockListID(unsigned);
    string getStockListName() const;              // returns the stocklist name
    StockMap &getStocks();                  // returns the whole stock map

    void setStockListName(const string &);  // can set the stock list name
};

#endif // STOCKLIST_H
