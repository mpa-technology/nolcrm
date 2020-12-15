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

bool TableStorageImport::crateTable(){
    if(DataBase::table().contains("storageImport")){
        self().tableCreate_ = true;
        return true;
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
        return false;
    }
    return true;
}




bool TableStorageImport::newImport(const ImportStorage& importStorage){
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
            return false;
        }

        return true;
    }




    return true;
}

