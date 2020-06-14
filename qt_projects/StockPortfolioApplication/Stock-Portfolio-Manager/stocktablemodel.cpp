/*
* stocktablemodel.cpp
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#include "stocktablemodel.h"
#include <QFont>

/*
 * Constructor
 */
StockTableModel::StockTableModel(StockList stockList, QObject *parent)
    : QAbstractTableModel(parent)
{
    setStocks(stockList);
}

void StockTableModel::setStocks(StockList stockList)
{
    StockMap sm = stockList.getStocks();
    for (auto s : sm)
    {
        Stock stock = s.second;
        stocks.push_back(stock);
    }
}

/*
 * Displays the headers, and data for headers
 */
QVariant StockTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        // set the column (Qt::Horizontal) headers
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Ticker Symbol");
            case 1:
                return QString("Company Name");
            case 2:
                return QString("Shares");
            case 3:
                return QString("Current Value");
            case 4:
                return QString("Change Percentage");
            case 5:
                return QString("Volume");
            case 6:
                return QString("Annual Dividend");
            }
        }
       }

    return QVariant();
}

/*
 * Returns number of rows in table model
 */
int StockTableModel::rowCount(const QModelIndex &parent) const
{
    return stocks.size();
}

/*
 * Returns number of columns in table model
 */
int StockTableModel::columnCount(const QModelIndex &parent) const
{
    // 7 columns
    return 7;
}

/*
 *  data - defines what data to display, where to display it, and how to display it
 */
QVariant StockTableModel::data(const QModelIndex &index, int role) const
{
    // Get the row and columns numbers from the given index (QModelIndex)
    int row = index.row();
    int col = index.column();

    // Qt::DisplayRole -> what data do we display and in what columns?
    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
        case 0: // ticker column
            return QString::fromStdString(stocks[row].getTicker());
            break;
        case 1: // company name column
            return QString::fromStdString(stocks[row].getCompanyName());
            break;
        case 2: // shares column
            return stocks[row].getShares();
            break;
        case 3: // current price column
            return stocks[row].getCurrentPrice();
            break;
        case 4: // percent change column
            return stocks[row].getCurrentPrice();
            break;
        case 5: // volume column
            return stocks[row].getVolume();
            break;
        case 6: // annual dividend column
            return stocks[row].getAnnualDividend();
            break;
        }
    }
    //  manages the fonts and font styles used in the view
    else if (role == Qt::FontRole)
    {
        // bold the text in the first column
        if (col == 0)
        {
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
    }
    // Qt::TextAlignRole -> controls how data is aligned inside cells
    else if(role == Qt::TextAlignmentRole)
    {
        // All columns after the Username column should be right-aligned
        // horizontally, and centered vertically.
        if (col > 1)
        {
            return Qt::AlignRight + Qt::AlignVCenter;
        }
    }

    return QVariant();
}

/*
 * setData - defines what data to display, where to display, and how to display it
 */
bool StockTableModel::setData(QModelIndex const &idx, QVariant const &value, int role)
{
    // Qt::EditRole: manages changes in the model
    if (Qt::EditRole == role)
    {
        // get the top left and bottom right indices of the cells in our update range
        QModelIndex topLeft = idx;
        QModelIndex bottomRight = index(this->rowCount() - 1, this->columnCount() -1);

        // emit events telling all listening event handlers
        // that both the data (from cell 0,0 to the end) AND the layout have changed
        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();

        return true;
    }
    return false;
}
