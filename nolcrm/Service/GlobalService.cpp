/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "GlobalService.hpp"

#include "GlobalEmitService.hpp"

#include "../DataBase/DataBase.hpp"
#include "../DataBase/TableOrders.hpp"
#include "../DataBase/TableProducts.hpp"


#include "../DataBase/TableStorage.hpp"
#include "../DataBase/TableStorageImport.hpp"
#include "../DataBase/TableStorageExport.hpp"

GlobalService::GlobalService(){

    Timers_.cache = new QTimer();
    Timers_.cache->setInterval(Settings::value("cache/autoClearCacheTime",50000).toInt());
    QObject::connect(Timers_.cache,SIGNAL(timeout()),&GlobalEmitService::self(),SLOT(emitGloablCacheClear()));


}

bool GlobalService::initDataBase_(){


    if(!DataBase::init())
        return false;

    if(!DataBase::open())
        return false;




    return true;
}

GlobalService &GlobalService::self(){
    static GlobalService sig;
    return sig;
}

void GlobalService::waekup(){
    try {
        GlobalService::self().initTableBase();
    } catch (const std::exception& exp) {
        qCritical()<<exp.what();
        return;
    }
    self().Timers_.cache->start();


}

void GlobalService::initTableBase(){

    if(!initDataBase_())
        throw std::runtime_error("Error init dataBase");
    else qDebug()<<"dataBase init: ok";


    TableProducts::crateTable();
    qDebug()<<"TableProducts crateTable: ok";

    TableOrders::crateTable();
    qDebug()<<"TableOrders crateTable: ok";

    TableStorage::crateTable();
    qDebug()<<"TableStorage crateTable: ok";

    TableStorageImport::crateTable();
    qDebug()<<"TableStorageImport crateTable: ok";

    TableStorageExport::crateTable();
    qDebug()<<"TableStorageExport crateTable: ok";


}



GlobalService::~GlobalService(){
    qDebug()<<"GlobalService down";
}


