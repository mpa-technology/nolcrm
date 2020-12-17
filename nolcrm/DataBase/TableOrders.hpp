/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_TABLEORDERS_HPP
#define NOLCRM_TABLEORDERS_HPP


#include <QVector>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>


#include "DataBase.hpp"






struct Order{
    struct product{
        quint64 id;
        quint64 price;
    };


    QVector<product>products;
    qint64 code = -1;
    QDate data;


    quint64 getSum()const{
    quint64 sum = 0;

    for(const auto& it : products)
    sum += it.price;

    return sum;
    }

    void addProduct(const product& pro){
        products.push_back(pro);
    }


};



class TableOrders{

    TableOrders();
    TableOrders(const TableOrders& root) = delete;
    TableOrders& operator=(const TableOrders&) = delete;

    static quint64 findFreeCode_();

    bool tableCreate_ = false;
    QSqlError lastError_;

public:

    static TableOrders& self();

    static QSqlError lastError();

    static bool crateTable();


    static QVector<Order> getAllOrder();

    static Order getOrderByCode(const quint64& code);

    static bool addOrder(const int& productId,const double& productPrice,const quint64& code,const QDate& data);

    static bool addOrder(QVector<QPair<int,double>>products,const QDate& data);

    static bool addOrder(QVector<QPair<int,double>>products,const quint64& code,const QDate& data);

    static bool removeOrderByCode(const quint64& code);

    static Order getOrderByData(const QDate& data);

    static QVector<Order> getOrderByData(const int& year, const int& month);
    static QVector<Order> getOrderByData(const int& year, const int& month, const int& day);



};


#endif