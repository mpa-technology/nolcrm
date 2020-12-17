 /*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "DataBase.hpp"


DataBase::DataBase(){}

DataBase::~DataBase(){
    qDebug()<<"DataBase down";
}

DataBase &DataBase::self(){
    static DataBase base;
    return base;
}



bool DataBase::init(){
    auto& base = self();
    auto& db = base.db();

    if(base.isInit_){
        qCritical()<<"db is init ";
        return false;
    }



    auto name = Settings::value("database/name","@NULL").toString();
    auto hostName = Settings::value("database/hostName","@CLEAR").toString();
    auto userName = Settings::value("database/userName","@CLEAR").toString();
    auto userPassword = Settings::value("database/userPassword","@CLEAR").toString();
    auto port = Settings::value("database/port",-1).toInt();
    auto driver = Settings::value("database/driver","@NULL").toString();


    if(name == "@NULL" || driver == "@NULL"){
        qCritical()<<"db name || driver == @NULL" << name << driver;
        return false;
    }


    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(name);


    if(hostName != "@CLEAR")
    db.setHostName(hostName);

    if(userName != "@CLEAR")
    db.setUserName(userName);

    if(userPassword != "@CLEAR")
    db.setPassword(userPassword);

    if(port != -1)
    db.setPort(port);

    base.isInit_ = true;
    return true;
}

QStringList DataBase::table(){
    return self().dataBase_.tables();
}

QSqlDatabase &DataBase::db(){
    return  self().dataBase_;
}

bool DataBase::open(){
    if(self().isOpen_)
        return {};

    self().dataBase_.open();

    if(self().dataBase_.lastError().type() == QSqlError::NoError)
        self().isOpen_ = true;


    if(self().dataBase_.lastError().type() != QSqlError::NoError){
        qCritical()<<self().dataBase_.lastError();
        return false;
    }

    return true;
}






