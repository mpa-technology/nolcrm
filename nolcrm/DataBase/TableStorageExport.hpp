/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once



#include <DataBase/DataBase.hpp>


struct ExportStorage{
    struct product{
        quint64 id;
        quint64 count;
        double price;
    };


    QVector<product>products;
    quint64 code = 0;
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

class TableStorageExport{
    TableStorageExport();
    TableStorageExport(const TableStorageExport& root) = delete;
    TableStorageExport& operator=(const TableStorageExport&) = delete;


    bool tableCreate_ = false;
    QSqlError lastError_;

    quint64 findFreeCode_();

public:

    static TableStorageExport& self();

    static QSqlError lastError();

    static void crateTable();

    static void newExport(const ExportStorage& importStorage);


    static QVector<ExportStorage> getAllExport();

    static ExportStorage getExport(const quint64& code);

    static void removeExportByCode(const quint64 &code);

};



