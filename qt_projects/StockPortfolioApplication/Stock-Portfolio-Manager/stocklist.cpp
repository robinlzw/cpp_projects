/*
* stocklist.cpp
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#include "stocklist.h"
#include <iostream>
using std::cout; using std::endl;

/*
 * Default Constructor
 */
StockList::StockList() :
           stockListName("")
{

}

/*
 * Constructor
 */
StockList::StockList(const string &name) :
           stockListName(name)
{

}

unsigned StockList::getStockListID()
{
    return stockListID;
}

void StockList::setStockListID(unsigned id)
{
    stockListID = id;
}

/*
 * Adds new stock to the map
 */
void StockList::addToMap(Stock stock)
{
    stocks.insert(make_pair(stock.getTicker(), stock));
}

/*
 * Removes stock from the map
 */
void StockList::removeFromMap(Stock stock)
{
    stocks.erase(stock.getTicker());
}

/*
 * Find and returns a stock
 */
Stock *StockList::findStock(const string &tick)
{
    // loops through stocks
    for (auto &s : stocks)
    {
        Stock &stock = s.second;

        // if found, returns stock reference
        if (stock.getTicker() == tick)
        {
            return &stock;
        }
    }
    // if not found...
    return nullptr;
}

/*
 * Returns the stock list name
 */
string StockList::getStockListName() const
{
    return stockListName;
}

/*
 * Returns the stock map
 */
StockMap &StockList::getStocks()
{
    return stocks;
}

/*
 * Sets stock list name
 */
void StockList::setStockListName(const string &name)
{
    stockListName = name;
}

