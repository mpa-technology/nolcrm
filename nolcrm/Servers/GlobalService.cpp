/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "GlobalService.hpp"

#include "UpdateService.hpp"

#include "../DataBase/DataBase.hpp"
#include "../DataBase/TableOrders.hpp"
#include "../DataBase/TableProducts.hpp"


#include "../DataBase/TableStorage.hpp"
#include "../DataBase/TableStorageImport.hpp"
#include "../DataBase/TableStorageExport.hpp"

GlobalService::GlobalService(){

    Timers_.cache = new QTimer();

    Timers_.cache->setInterval(Settings::value("cache/autoClearCacheTime",50000).toInt());
    //Timers_.cache->
    QObject::connect(Timers_.cache,SIGNAL(timeout()),&UpdateService::self(),SLOT(emitGloablCacheClear()));


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

bool GlobalService::waekup(){
    try {
        GlobalService::self().initTableBase();
    } catch (const std::exception& exp) {
        qCritical()<<exp.what();
        return false;
    }
    self().Timers_.cache->start();


    return true;
}

void GlobalService::initTableBase(){

    if(!initDataBase_())
        throw std::runtime_error("Error init dataBase");
    else qDebug()<<"dataBase init: ok";


    if(!TableProducts::crateTable())
        throw std::runtime_error("Error init TableProducts");
    else qDebug()<<"TableProducts crateTable: ok";

    if(!TableOrders::crateTable())
        throw std::runtime_error("Error init TableOrders");
    else qDebug()<<"TableOrders crateTable: ok";

    if(!TableStorage::crateTable())
        throw std::runtime_error("Error init TableStorage");
    else qDebug()<<"TableStorage crateTable: ok";

    if(!TableStorageImport::crateTable())
        throw std::runtime_error("Error init TableStorageImport");
    else qDebug()<<"TableStorageImport crateTable: ok";

    if(!TableStorageExport::crateTable())
        throw std::runtime_error("Error init TableStorageExport");
    else qDebug()<<"TableStorageExport crateTable: ok";


}



GlobalService::~GlobalService(){
    qDebug()<<"GlobalService down";
}



#include "ImportService.hpp"
#include "ExportService.hpp"
#include "ProductService.hpp"


size_t GlobalService::cacheSize(){

    return ImportService::cacheSize() + ExportService::cacheSize() + ProductService::cacheSize();
}
