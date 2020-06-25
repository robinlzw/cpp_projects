/*
* stock.h
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#ifndef STOCK_H
#define STOCK_H

#include <string>
using std::string;

/*
 * Represents a stock object. Stores information describing
 * an instance of a stock.
 */
class Stock
{
private:
    // Each of these will describe a stock object.
    string ticker;
    string companyName;
    double currentPrice;
    double percentChange;
    int    volume;
    double annualDividend;
    int    shares;

public:
    // Default Constructor
    Stock();
    // Two Parameter Constructor
    Stock(const string &, const string &);
    // Five Parameter Constructor
    Stock(const string &, const string &, double, double, int, double, int);

    // Getters
    string getTicker() const         { return ticker; }
    string getCompanyName() const    { return companyName; }
    double getCurrentPrice() const  { return currentPrice; }
    double getPercentChange() const { return percentChange; }
    int    getVolume()    const     { return volume; }
    double getAnnualDividend() const { return annualDividend; }
    int    getShares()   const      { return shares; }

    // Setters
    void setTicker(const string &);
    void setCompanyName(const string &);
    void setCurrentPrice(double);
    void setPercentChange(double);
    void setVolume(int);
    void setAnnualDividend(double);
    void setShares(int);
};

#endif // STOCK_H
