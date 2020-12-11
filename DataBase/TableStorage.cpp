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

QSqlError TableStorage::addItem(const quint64 &id){
    QSqlQuery query(DataBase::db());

    query.prepare( R"( INSERT INTO storage(ProductsId,ProductsCount) VALUES(:ProductsId,:ProductsCount); )" );
    query.bindValue(":ProductsId",id);
    query.bindValue(":ProductsCount",0);
    query.exec();

    return query.lastError();
}

bool TableStorage::itemExist(const quint64 &id){

    QSqlQuery query(DataBase::db());
    query.prepare("SELECT * FROM storage WHERE Id=:Id ;");
    query.exec();
    query.next();
    qDebug()<<query.value(0);



}
