/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_TABLESTORAGEEXPORT_HPP
#define NOL_CRM_TABLESTORAGEEXPORT_HPP
#include <DataBase/DataBase.hpp>


struct ExportStorage{
    struct product{
        quint64 id;
        quint64 count;
        quint64 price;
    };


    QVector<product>products;
    qint64 code = -1;
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

    static bool crateTable();

    static bool newExport(const ExportStorage& importStorage);


    static QVector<ExportStorage> getAllExport();

    static ExportStorage getExport(const quint64& code);


};



#endif // TABLESTORAGEEXPORT_HPP
