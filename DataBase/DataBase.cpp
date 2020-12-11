#include "DataBase.hpp"


DataBase::DataBase(){}

DataBase &DataBase::self(){
    static DataBase base;
    return base;
}

void DataBase::init(const QString &dataBaseName, const QString &hostName, const QString &userName, const QString &userPassword, const QString &dataBaseDriver){
    auto& base = self();

    if(base.isInit_)
        return;

    base.dataBase_ = QSqlDatabase::addDatabase(dataBaseDriver);

    base.dataBase_.setDatabaseName(dataBaseName);

    base.dataBase_.setPort(5432);


    if(!hostName.isEmpty()) base.dataBase_.setHostName(hostName);

    if(!userName.isEmpty()) base.dataBase_.setUserName(userName);

    if(!userPassword.isEmpty()) base.dataBase_.setPassword(userName);

    base.isInit_ = true;

}

QStringList DataBase::table(){
    return self().dataBase_.tables();
}

QSqlDatabase &DataBase::db(){
    return  self().dataBase_;
}

QSqlError DataBase::open(){
    if(self().isOpen_)
        return {};

    self().dataBase_.open();

    if(self().dataBase_.lastError().type() == QSqlError::NoError)
        self().isOpen_ = true;

    return self().dataBase_.lastError();
}






