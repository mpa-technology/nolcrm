/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "TableStorage.hpp"



TableStorage::TableStorage(){}

TableStorage &TableStorage::self(){
    static TableStorage sig;
    return sig;
}

QSqlError TableStorage::lastError(){
    return TableStorage::self().lastError_;
}

bool TableStorage::crateTable(){

    if(DataBase::table().contains("storage")){
        TableStorage::self().tableCreate_ = true;
        return true;
    }

    QSqlQuery query(DataBase::db());


    query.prepare(R"(CREATE TABLE storage (
                  Id	INTEGER PRIMARY KEY,
                  ProductsId	INTEGER,
                  ProductsCount INTEGER
                  );)");
    query.exec();


    if(query.lastError().type() != QSqlError::NoError){
        qCritical()<<query.lastError();
        TableStorage::self().tableCreate_ = false;
        TableStorage::self().lastError_ = query.lastError();
        return false;
    }

    TableStorage::self().tableCreate_ = true;


    return true;
}

bool TableStorage::addItem(const quint64 &id){
    QSqlQuery query(DataBase::db());

    query.prepare( R"( INSERT INTO storage(ProductsId,ProductsCount) VALUES(:ProductsId,:ProductsCount); )" );
    query.bindValue(":ProductsId",id);
    query.bindValue(":ProductsCount",0);
    query.exec();

    if(query.lastError().type()!=QSqlError::NoError){
        qWarning()<<query.lastError();
        return false;
    }

    return true;
}

bool TableStorage::setCount(const quint64 &id, const quint64 &count){
    QSqlQuery query(DataBase::db());
    query.prepare("UPDATE storage SET ProductsCount = :count  WHERE ProductsId=:Id ;");
    query.bindValue(":count",count);
    query.bindValue(":Id",id);
    query.exec();
    return query.lastError().type() == query.lastError().NoError;
}

bool TableStorage::addCount(const quint64 &id, const quint64 &count)
{
    QSqlQuery query(DataBase::db());
    query.prepare("UPDATE storage SET ProductsCount=:count WHERE ProductsId=:Id;");
    query.bindValue(":count",count+getCount(id));
    query.bindValue(":Id",id);
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qWarning()<<query.lastError();
        return false;
    }

    return true;
}


bool TableStorage::subCount(const quint64 &id, const quint64 &count){

//    if(subOverflow(getCount(id),count)){
//        qWarning()<<"count - currentCount < 0";
//        return false;
//    }

    QSqlQuery query(DataBase::db());
    query.prepare("UPDATE storage SET ProductsCount=:count WHERE ProductsId=:Id;");
    query.bindValue(":count",getCount(id)-count);
    query.bindValue(":Id",id);
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qWarning()<<query.lastError();
        return false;
    }

    return true;
}

quint64 TableStorage::getCount(const quint64 &id)
{
    QSqlQuery query(DataBase::db());
    query.prepare("SELECT * FROM storage WHERE ProductsId=:Id ;");
    query.bindValue(":Id",id);
    query.exec();
    query.next();

    return query.value("ProductsCount").toULongLong();;
}

Storage TableStorage::getItem(const quint64 &id){
    Storage storage;


    QSqlQuery query(DataBase::db());
    query.prepare("SELECT * FROM storage WHERE ProductsId=:Id ;");
    query.bindValue(":Id",id);
    query.exec();

    query.next();

   storage.pid =  query.value("ProductsId").toULongLong();
   storage.count =  query.value("ProductsCount").toULongLong();;


   return storage;
}

bool TableStorage::itemExist(const quint64 &id){

    QSqlQuery query(DataBase::db());
    query.prepare("SELECT * FROM storage WHERE Id=:Id ;");
    query.exec();
    query.next();
    qDebug()<<query.value(0);

    return query.value(0).toBool();
}
