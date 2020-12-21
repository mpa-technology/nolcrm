/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#include "TableOrders.hpp"
#include "DataBase.hpp"

TableOrders::TableOrders(){}


void TableOrders::addOrder(const int &productId, const double &productPrice, const quint64 &code, const QDate &data){

    QSqlQuery query(DataBase::db());
    query.prepare( R"( INSERT INTO orders(Code,ProductsId,ProductsPrice,Data) VALUES(:Code,:ProductsId,:ProductsPrice,:Data); )" );
    query.bindValue(":Code",code);
    query.bindValue(":ProductsId",productId);
    query.bindValue(":ProductsPrice",productPrice);
    query.bindValue(":Data",data);
    query.exec();


    if(query.lastError().type()!=QSqlError::NoError){
        qWarning()<<query.lastError();
        throw retrunDBError(query.lastError());
    }


}


quint64 TableOrders::findFreeCode_(){

    QSqlQuery query;
    query.prepare("SELECT Code FROM orders");
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qCritical()<<query.lastError();
        self().tableCreate_ = false;
        self().lastError_ = query.lastError();
        throw retrunDBError(query.lastError());
    }


    QVector<quint64>codes;

    while (query.next())
        codes.push_back(query.value("Code").toULongLong());


    quint64 code = 1;

    while (codes.indexOf(code)!=-1) {
        code++;
    }


    return code;
}

TableOrders &TableOrders::self(){
    static TableOrders sig;
    return sig;
}

QSqlError TableOrders::lastError(){
    return TableOrders::self().lastError_;
}

void TableOrders::crateTable(){

    if(DataBase::table().contains("orders")){
        TableOrders::self().tableCreate_ = true;
        return;
    }

    QSqlQuery query(DataBase::db());


    query.prepare(R"(CREATE TABLE orders(
                  Id	INTEGER PRIMARY KEY,
                  Code	INTEGER,
                  ProductsId INTEGER,
                  ProductsPrice	REAL,
                  Data DATA
                  );)");
    query.exec();


    if(query.lastError().type() != QSqlError::NoError){
        qCritical()<<query.lastError();
        TableOrders::self().tableCreate_ = false;
        TableOrders::self().lastError_ = query.lastError();
        throw retrunDBError(query.lastError());
    }

    TableOrders::self().tableCreate_ = true;

}

QVector<Order> TableOrders::getAllOrder(){
    QSqlQuery query(DataBase::db());
    query.prepare(R"(SELECT * FROM orders )");
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qWarning()<<query.lastError();
       throw retrunDBError(query.lastError());
    }



    QMap<qint64,Order>mapExportStorage;



    while (query.next()) {
        auto code = query.value("Code").toLongLong();

        auto ProductsId = query.value("ProductsId").toLongLong();
        auto ProductsPrice = query.value("ProductsPrice").toDouble();
        auto Data = query.value("Data").toDate();


        Order::product pro;
        pro.id = ProductsId;
        pro.price = ProductsPrice;

        if(mapExportStorage.find(code)==mapExportStorage.end()){
            Order stg;
            stg.code = code;
            stg.data = Data;
            stg.addProduct(pro);
            mapExportStorage.insert(code,stg);
            continue;
        }


        mapExportStorage.find(code).value().addProduct(pro);



    }


    QVector<Order>listExportStorage;

    for(auto it: mapExportStorage)
        listExportStorage.push_back(it);


    return listExportStorage;
}


void TableOrders::addOrder(QVector<QPair<int, double> > products, const QDate &data){

    auto code = findFreeCode_();

    for(const auto&it:products){
       addOrder(it.first,it.second,code,data);

    }


}

void TableOrders::addOrder(QVector<QPair<int, double> > products, const quint64 &code, const QDate &data){


    for(const auto&it:products)
        addOrder(it.first,it.second,code,data);



}

Order TableOrders::getOrderByCode(const quint64 &code){

    for(const auto& it :  getAllOrder())
        if(it.code == code)
            return it;

    return {};
}

void TableOrders::removeOrderByCode(const quint64 &code){
    QSqlQuery query;
    query.prepare("DELETE FROM orders WHERE Code = :code");
    query.bindValue(":code",code);
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qDebug()<<query.lastError();
        throw retrunDBError(query.lastError());
    }


}

Order TableOrders::getOrderByData(const QDate &data){


    for(const auto& it : getAllOrder())
        if(it.data == data)
            return it;

    return {};
}

QVector<Order> TableOrders::getOrderByData(const int &year, const int &month){


    QVector<Order> list;

    for(const auto& it : getAllOrder())
        if(it.data.month() == month && it.data.year())
            list.push_back(it);

    return list;
}

QVector<Order> TableOrders::getOrderByData(const int &year, const int &month, const int &day)
{
    QVector<Order> list;

    for(const auto& it : getAllOrder())
        if(it.data.month() == month && it.data.year() && it.data.day() == day)
            list.push_back(it);

    return list;
}
