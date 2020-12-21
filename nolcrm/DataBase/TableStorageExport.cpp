/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "TableStorageExport.hpp"


TableStorageExport::TableStorageExport(){}

quint64 TableStorageExport::findFreeCode_(){
    QSqlQuery query;
    query.prepare("SELECT Code FROM storageExport");
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

TableStorageExport &TableStorageExport::self(){
    static TableStorageExport sig;
    return sig;
}

QSqlError TableStorageExport::lastError(){
    return self().lastError_;
}

void TableStorageExport::crateTable(){
    if(DataBase::table().contains("storageExport")){
        self().tableCreate_ = true;
    }

    QSqlQuery query(DataBase::db());


    query.prepare(R"(CREATE TABLE storageExport (
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

void TableStorageExport::newExport(const ExportStorage &importStorage){
    auto code = self().findFreeCode_();
    QSqlQuery query(DataBase::db());
    for(const auto& it : importStorage.products){

        query.prepare(R"(INSERT INTO storageExport(Code,ProductsId,ProductsCount,ProductsPrice,Data) VALUES(:Code,:ProductsId,:ProductsCount,:ProductsPrice,:Data);)");

        query.bindValue(":Code",code);
        query.bindValue(":ProductsId",it.id);
        query.bindValue(":ProductsCount",it.count);
        query.bindValue(":ProductsPrice",it.price);
        query.bindValue(":Data",importStorage.data);

        query.exec();

        if(query.lastError().type() != QSqlError::NoError){
            qWarning()<<query.lastError();
            throw  retrunDBError(query.lastError());
        }
    }


}

QVector<ExportStorage> TableStorageExport::getAllExport(){
    QSqlQuery query(DataBase::db());
    query.prepare("SELECT * FROM storageExport");
    if(!query.exec()){
        qCritical()<<query.lastError();
    }


    QMap<qint64,ExportStorage>mapExportStorage;



    while (query.next()) {
        auto code = query.value("Code").toLongLong();
        auto ProductsCount = query.value("ProductsCount").toLongLong();
        auto ProductsId = query.value("ProductsId").toLongLong();
        auto ProductsPrice = query.value("ProductsPrice").toDouble();
        auto Data = query.value("Data").toDate();


        ExportStorage::product pro;
        pro.id = ProductsId;
        pro.count = ProductsCount;
        pro.price = ProductsPrice;

        if(mapExportStorage.find(code)==mapExportStorage.end()){
            ExportStorage stg;
            stg.code = code;
            stg.data = Data;
            stg.addProduct(pro);
            mapExportStorage.insert(code,stg);
            continue;
        }


        mapExportStorage.find(code).value().addProduct(pro);



    }


    QVector<ExportStorage>listExportStorage;

    for(auto it: mapExportStorage)
        listExportStorage.push_back(it);


    return listExportStorage;
}

ExportStorage TableStorageExport::getExport(const quint64& code){

    for(auto& it : getAllExport())
        if(it.code == code)
            return it;

    return {};
}
