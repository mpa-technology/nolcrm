#pragma once
#include <QVector>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>


#include "DataBase.hpp"

struct Orders{
    quint64 id;
    quint64 code;
    QPair<int,double> product;
};


struct Order{

    double fpice;
    QDate data;
    quint64 code;
    QVector<quint64>orders;
    QVector<quint64>products;
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


    //TODO:rename
    typedef QVector<QPair<quint64,QVector<Orders>>>  hordersList;
    typedef QVector<Orders>  ordersList;

    //TODO:rename
    static hordersList hgetAllOrder();
    //TODO:rename
    static QVector<Order> hhgetAllOrder();

    static ordersList getAllOrder();

    static Order hhgetOrderByCode(const quint64& code);

    static QSqlError addOrder(const int& productId,const double& productPrice,const quint64& code,const QDate& data);

    static QSqlError addOrder(QVector<QPair<int,double>>products,const QDate& data);

    static QSqlError addOrder(QVector<QPair<int,double>>products,const quint64& code,const QDate& data);

    static QSqlError removeOrderByCode(const quint64& code);

    //TODO:rename
    static Order hgetOrderByData(const QDate& data);

    //TODO:rename
    static QVector<Order> hgetOrderByData(const int& year, const int& month);



};
