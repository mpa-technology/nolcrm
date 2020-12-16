#pragma once
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

    static  QSqlError addProduct( const Product& product);

    static QSqlError addProduct( const QString& name,const QString& category,const QString& manufacturer, const double& price, const double& manufacturerPrice,const QString& descriptions);

    static bool editProduct(const Product& product);


    static QSqlError removeProduct(const quint64& id);

    static productList getAllProduct();

    static QPair<QSqlError,Product> getProductById(const quint64& id);

};
