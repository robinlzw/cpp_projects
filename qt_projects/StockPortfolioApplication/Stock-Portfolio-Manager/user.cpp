/*
 * user.cpp
 * Authors: Christian Kimball, Nicholas Hagan, Zachery Forsythe
 * Fall 2017
 * Course: CS245 - OOP w/ C++
 */

#include "user.h"
#include <exception>
#include <utility>

/*
 * Default constructor
 */
User::User()
{
}

/*
 * Two Paramere Constructor
 * Initializes username and password hash
 */
User::User(const std::string &name, const std::string &pass)
{
    this->setUsername(name);
    this->setPassHash(pass);
}

/*
 * Three Parameter Constructor
 * Initializes all data members
 */
User::User(int id, const string &name, const string &pass) :
    userID(id)
{
    this->setUsername(name);
    this->setPassHash(pass);
}

/*
 * Destructor
 * Removes all data members from memory
 */
User::~User()
{
}

/*
 * Sets the ID of the user
 */
void User::setUserID(int id)
{
    userID = id;
}

/*
 * Sets the username of the User
 * Checks to make sure username meets all requirements
 */
void User::setUsername(const string &name)
{
    username = name;
}

/*
 * Sets the hashed password of the User
 * Checks to see if the hashed password is empty
 */
void User::setPassHash(const string &pass)
{
    passHash = pass;
}

/*
 * Searches for a given stock list by its name
 */
StockList* User::findStockList(const string &stockListName)
{
    //search the map for the given StockList's name
    auto it = stockLists.find(stockListName);

    //check to see if the StockList wasn't found
    if(it == stockLists.end())
    {
        //if it wasn't return a null pointer
        return nullptr;
    }

    //if it was return a pointer to it
    StockList *sl = &it->second;
    return sl;
}

/*
 * Adds a StockList to the map
 * Checks to see if the StockList already exists in the map
 */
void User::addStockList(StockList sl)
{
    //check if the StockList to be added already exists
    //call findStockList() to do this
    if(findStockList(sl.getStockListName()) == nullptr)
    {
        //if it does not exist add it
        stockLists.insert(std::make_pair(sl.getStockListName(), sl));
    }
    else
    {
        //already exists, throw exception
        throw std::invalid_argument("StockList already exists");
    }
}

/*
 * Remove a stock list from the map
 * Checks to see if the Stock list exists in the map
 */
void User::removeStockList(const string &stockListName)
{
    //check to see if the StockList exists in the map
    //call findStockList() to do this
    if(findStockList(stockListName) == nullptr)
    {
        //if it does not exist in the map, throw exception
        throw std::out_of_range("StockList does not exist, could not be removed");
    }
    else
    {
        //if it does exist in the map, remove it
        stockLists.erase(stockListName);
    }
}
