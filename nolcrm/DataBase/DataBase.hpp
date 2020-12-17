/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_DATABASE_HPP
#define NOLCRM_DATABASE_HPP

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <Settings/Settings.hpp>


class DataBase{

    QSqlDatabase dataBase_;

    bool isInit_ = false;
    bool isOpen_ = false;

    DataBase();
    DataBase(const DataBase& root) = delete;
    DataBase& operator=(const DataBase&) = delete;



public:
    ~DataBase();

    static DataBase& self();

    static bool init();


    static QStringList table();

    static QSqlDatabase& db();

    static bool open();






};



#endif
