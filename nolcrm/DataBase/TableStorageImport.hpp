/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#pragma once


#include <DataBase/DataBase.hpp>


struct ImportStorage{
    struct product{
        quint64 id;
        quint64 count;
        double price;
    };


    QVector<product>products;
    quint64 code = -1;
    QDate data;


    quint64 getSum()const{
    quint64 sum = 0;

    for(const auto& it : products)
    sum += it.price;

    return sum;
    }

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

    static void crateTable();

    static void newImport(const ImportStorage& importStorage);

    static QVector<ImportStorage> getAllImport();

    static ImportStorage getImport(const quint64 &code);


    static void removeImportByCode(const quint64 &code);

};



