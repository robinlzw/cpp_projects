/*
* stocktablemodel.h
* Author: Nicholas Hagan, Christian Kimball, Zachery Forsythe
* Fall 2017
* Course: CS245: OOP w/ C++
*/

#ifndef STOCKTABLEMODEL_H
#define STOCKTABLEMODEL_H

#include <QAbstractTableModel>
#include "stock.h"
#include "dbmanager.h"
#include <vector>
using std::vector;

class StockTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit StockTableModel(StockList, QObject *parent = nullptr);

    // Header:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void setStocks(StockList);



private:
    vector<Stock> stocks;

};

#endif // STOCKTABLEMODEL_H
