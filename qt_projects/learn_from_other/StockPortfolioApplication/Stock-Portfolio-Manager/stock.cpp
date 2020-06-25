/*
* stock.cpp
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#include "stock.h"

/*
 *  Default Constructor
 */
Stock::Stock()
{
    // Initializes data members with base values
    ticker = "";
    companyName = "";
    currentPrice = 0;
    percentChange = 0;
    volume = 0;
    annualDividend = 0;
    shares = 0;
}

/*
 * Two Parameter constructor, initializes ticker
 * and companyName through parameters
 */
Stock::Stock(const string &tick, const string &name) :
             ticker(tick), companyName(name)
{
    // Initializes remaining datamembers with base values
    currentPrice = 0;
    percentChange = 0;
    volume = 0;
    annualDividend = 0;
    shares = 0;
}

/*
 * Five Parameter constructor, initializes
 * all data members through parameters
 */
Stock::Stock(const string &tick, const string &name, double price, double change, int vol, double dividend, int shar) :
             ticker(tick), companyName(name), currentPrice(price), percentChange(change), volume(vol),
             annualDividend(dividend), shares(shar)
{

}

/*
 * Setters
 */
void Stock::setTicker(const string &tick) { ticker = tick; }
void Stock::setCompanyName(const string &name) { companyName = name; }
void Stock::setCurrentPrice(double price) { currentPrice = price; }
void Stock::setPercentChange(double change) { percentChange = change; }
void Stock::setVolume(int vol) { volume = vol; }
void Stock::setAnnualDividend(double dividend) { annualDividend = dividend; }
void Stock::setShares(int shar) { shares = shar; }

