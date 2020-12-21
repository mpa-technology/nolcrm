/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_TABLESTORAGE_HPP
#define NOLCRM_TABLESTORAGE_HPP

#include "../Tool.hpp"
#include "DataBase.hpp"


struct Storage{
quint64 pid;
quint64 count;
};


class TableStorage{


    TableStorage();
    TableStorage(const TableStorage& root) = delete;
    TableStorage& operator=(const TableStorage&) = delete;


    bool tableCreate_ = false;
    QSqlError lastError_;

public:

    static TableStorage& self();

    static QSqlError lastError();

    static void crateTable();

    static void addItem(const quint64& id);

    static void setCount(const quint64& id,const quint64& count);
    static void addCount(const quint64& id,const quint64& count);
    static void subCount(const quint64& id,const quint64& count);

    static quint64 getCount(const quint64& id);

    static Storage getItem(const quint64& id);




};


#endif
