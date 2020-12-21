/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#include "TableStorageImport.hpp"

quint64 TableStorageImport::findFreeCode_(){

    QSqlQuery query;
    query.prepare("SELECT Code FROM storageImport");
    query.exec();

    QVector<quint64>codes;

    while (query.next())
        codes.push_back(query.value("Code").toULongLong());


    quint64 code = 1;

    while (codes.indexOf(code)!=-1) {
        code++;
    }


    return code;
}


TableStorageImport::TableStorageImport(){}

TableStorageImport &TableStorageImport::self(){
    static TableStorageImport sig;
    return sig;
}

QSqlError TableStorageImport::lastError(){
    return self().lastError_;
}

void TableStorageImport::crateTable(){
    if(DataBase::table().contains("storageImport")){
        self().tableCreate_ = true;
        return ;
    }

    QSqlQuery query(DataBase::db());


    query.prepare(R"(CREATE TABLE storageImport (
                  Id	INTEGER PRIMARY KEY,
                  Code	INTEGER,
                  ProductsId INTEGER,
                  ProductsCount INTEGER,
                  ProductsPrice REAL,
                  Data DATA
                  );)");


    query.exec();


    if(query.lastError().type() != QSqlError::NoError){
        qCritical()<<query.lastError();
        self().tableCreate_ = false;
        self().lastError_ = query.lastError();
        throw retrunDBError(query.lastError());
    }

}




void TableStorageImport::newImport(const ImportStorage& importStorage){
    auto code = self().findFreeCode_();
    QSqlQuery query(DataBase::db());

    for(const auto& it : importStorage.products){

        query.prepare(R"(INSERT INTO storageImport(Code,ProductsId,ProductsCount,ProductsPrice,Data) VALUES(:Code,:ProductsId,:ProductsCount,:ProductsPrice,:Data);)");

        query.bindValue(":Code",code);
        query.bindValue(":ProductsId",it.id);
        query.bindValue(":ProductsCount",it.count);
        query.bindValue(":ProductsPrice",it.price);
        query.bindValue(":Data",importStorage.data);

        query.exec();

        if(query.lastError().type() != QSqlError::NoError){
            qWarning()<<query.lastError();
           throw retrunDBError(query.lastError());
        }


    }



}

QVector<ImportStorage> TableStorageImport::getAllImport(){
    QSqlQuery query(DataBase::db());
    query.prepare("SELECT * FROM storageImport");
    if(!query.exec()){
        qCritical()<<query.lastError();
    }


    QMap<qint64,ImportStorage>mapExportStorage;



    while (query.next()) {
        auto code = query.value("Code").toLongLong();
        auto ProductsCount = query.value("ProductsCount").toLongLong();
        auto ProductsId = query.value("ProductsId").toLongLong();
        auto ProductsPrice = query.value("ProductsPrice").toDouble();
        auto Data = query.value("Data").toDate();


        ImportStorage::product pro;
        pro.id = ProductsId;
        pro.count = ProductsCount;
        pro.price = ProductsPrice;

        if(mapExportStorage.find(code)==mapExportStorage.end()){
            ImportStorage stg;
            stg.code = code;
            stg.data = Data;
            stg.addProduct(pro);
            mapExportStorage.insert(code,stg);
            continue;
        }


        mapExportStorage.find(code).value().addProduct(pro);



    }


    QVector<ImportStorage>listExportStorage;

    for(auto it: mapExportStorage)
        listExportStorage.push_back(it);


    return listExportStorage;
}

ImportStorage TableStorageImport::getImport(const quint64 code){

    for(auto& it : getAllImport())
        if(it.code == code)
            return it;

    return {};
}

