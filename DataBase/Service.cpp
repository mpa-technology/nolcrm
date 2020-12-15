#include "Service.hpp"
GlobalService::GlobalService(){}

bool GlobalService::initDataBase_(){
    auto& settings = Settings::self();
    QString dataBaseName = settings.value("database/name","@NULL").toString();
    QString hostName = settings.value("database/hostName","@NULL").toString();
    QString userName = settings.value("database/userName","@NULL").toString();
    QString userPassword = settings.value("database/userPassword","@NULL").toString();
    QString dataBaseDriver = settings.value("database/driver","@NULL").toString();

    qDebug()<<dataBaseName;

    if(dataBaseName == "@NULL" || hostName == "@NULL" || userName == "@NULL" || userPassword=="@NULL" || dataBaseDriver=="@NULL"){
        qCritical()<<"int db faill";
        return false;
    }



    DataBase::init(dataBaseName,hostName,userName,userPassword,dataBaseDriver);
    QSqlError error = DataBase::open();

    if(; error.type() != QSqlError::NoError){
        qWarning()<<error;
        return false;
    }



    return true;
}

GlobalService &GlobalService::self(){
    static GlobalService sig;
    return sig;
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
    else qDebug()<<"TableStorageImport crateTable: ok";


}
