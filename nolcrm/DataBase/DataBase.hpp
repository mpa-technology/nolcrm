/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once


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

class retrunDBError : public std::exception{
    QString errorText_;
    QSqlError errorSql_;
public:

    retrunDBError(){}
    retrunDBError(const QSqlError& error){
        errorText_ =   error.text();
        errorSql_ = error;
    }
    retrunDBError(const QString& errorText){
        errorText_ = errorText;
    }

    virtual  ~retrunDBError(){}

    virtual const char* wath()const{
        return  errorText_.toStdString().data();
    }

    QSqlError error()const{
        return  errorSql_;
    }

    QString qstring()const{
        return  errorText_;
    }

};


