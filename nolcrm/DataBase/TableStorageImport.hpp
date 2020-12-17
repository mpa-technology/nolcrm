#ifndef NOLCRM_TABLESTORAGEIMPORT_HPP
#define NOLCRM_TABLESTORAGEIMPORT_HPP


#include "DataBase.hpp"


struct ImportStorage{
    struct product{
        quint64 id;
        quint64 count;
        quint64 price;
    };


    QVector<product>products;
    qint64 code = -1;
    QDate data;

    void addProduct(const product& pro){
        products.push_back(pro);
    }


};

class TableStorageImport{


    TableStorageImport();
    TableStorageImport(const TableStorageImport& root) = delete;
    TableStorageImport& operator=(const TableStorageImport&) = delete;


    bool tableCreate_ = false;
    QSqlError lastError_;

    quint64 findFreeCode_();

public:

    static TableStorageImport& self();

    static QSqlError lastError();

    static bool crateTable();

    static bool newImport(const ImportStorage& importStorage);

    static QVector<ImportStorage> getAllImport();

    static ImportStorage getImport(const quint64 code){

        for(auto& it : getAllImport())
            if(it.code == code)
                return it;

        return {};
    }

};


class TableStorageExport{
    TableStorageExport(){}
    TableStorageExport(const TableStorageExport& root) = delete;
    TableStorageExport& operator=(const TableStorageExport&) = delete;


    bool tableCreate_ = false;
    QSqlError lastError_;

    quint64 findFreeCode_(){
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

public:

    static TableStorageExport& self(){
        static TableStorageExport sig;
        return sig;
    }

    static QSqlError lastError(){
        return self().lastError_;
    }

    static bool crateTable(){
        if(DataBase::table().contains("storageExport")){
            self().tableCreate_ = true;
            return true;
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
            return false;
        }
        return true;
    }

    static bool newExport(const ImportStorage& importStorage){
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
                return false;
            }
        }

        return true;
    }


    static QVector<ImportStorage> getAllExport(){
        QSqlQuery query(DataBase::db());
        query.prepare("SELECT * FROM storageExport");
        if(!query.exec()){
            qCritical()<<query.lastError();
        }

        QVector<ImportStorage>f;

        ImportStorage stg;
        stg.code = -1;

        while (query.next()) {
            auto code = query.value("Code").toLongLong();
            auto ProductsCount = query.value("ProductsCount").toLongLong();
            auto ProductsId = query.value("ProductsId").toLongLong();
            auto ProductsPrice = query.value("ProductsId").toDouble();
            auto Data = query.value("Data").toDate();

            ImportStorage::product pro;
            pro.id = ProductsId;
            pro.count = ProductsCount;
            pro.price = ProductsPrice;

            if(stg.code == -1){
                stg.addProduct(pro);
                stg.code = code;
                stg.data = Data;
                continue;
            }


            if(stg.code == code){
                stg.addProduct(pro);
                continue;
            }

            f.push_back(stg);
            stg = ImportStorage();
            stg.code = -1;

        }

        if(stg.code != -1)
            f.push_back(stg);

        return f;
    }

    static ImportStorage getExport(const quint64 code){

        for(auto& it : getAllExport())
            if(it.code == code)
                return it;

        return {};
    }


};

#endif
