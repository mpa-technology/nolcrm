#pragma once
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


    };
