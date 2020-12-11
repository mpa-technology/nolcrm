#pragma once
#include "DataBase.hpp"


class TableStorage{


    TableStorage();
    TableStorage(const TableStorage& root) = delete;
    TableStorage& operator=(const TableStorage&) = delete;


    bool tableCreate_ = false;
    QSqlError lastError_;

public:

    static TableStorage& self();

    static QSqlError lastError();

    static bool crateTable();

    static QSqlError addItem(const quint64& id);


    //TODO: not test
    static bool itemExist(const quint64& id);

};

