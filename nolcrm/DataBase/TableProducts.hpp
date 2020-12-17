/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#ifndef NOLCRM_TABLEPRODUCTS_HPP
#define NOLCRM_TABLEPRODUCTS_HPP


#include <QVector>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

#include "DataBase.hpp"

struct Product{
    quint64 id;
    QString name;
    QString category;
    QString manufacturer;
    QString descriptions;
    double price;
    double manufacturerPrice;
};


class TableProducts{


    TableProducts();
    TableProducts(const TableProducts& root) = delete;
    TableProducts& operator=(const TableProducts&) = delete;

    bool tableCreate_ = false;

    QSqlError lastError_;

public:

    static TableProducts& self();

    static QSqlError lastError();

    typedef  QVector<Product> productList;

    static bool crateTable();

    static Product lastProduct();

    static  bool addProduct( const Product& product);

    static bool addProduct( const QString& name,const QString& category,const QString& manufacturer, const double& price, const double& manufacturerPrice,const QString& descriptions);

    static bool editProduct(const Product& product);

    static bool removeProduct(const quint64& id);

    static productList getAllProduct();

    static Product getProductById(const quint64& id);

};


#endif
