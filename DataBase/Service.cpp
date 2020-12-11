#include "Service.hpp"

GlobalService::GlobalService(){}

bool GlobalService::initDataBase_(){
    QSettings settings("mpacrm.conf",QSettings::NativeFormat);

    QString dataBaseName = settings.value("database/dataBaseName","nolBase.db").toString();
    QString hostName = settings.value("database/hostName",QString()).toString();
    QString userName = settings.value("database/userName",QString()).toString();
    QString userPassword = settings.value("database/userPassword",QString()).toString();
    QString dataBaseDriver = settings.value("database/dataBaseDriver","QSQLITE").toString();


    DataBase::init(dataBaseName,hostName,userName,userPassword,dataBaseDriver);
    QSqlError error = DataBase::open();

    if(; error.type() != QSqlError::NoError){
        qWarning()<<error;
        return false;
    }


    settings.sync();

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



}
