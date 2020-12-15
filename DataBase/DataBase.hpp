#pragma once
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>



class DataBase{

    QSqlDatabase dataBase_;

    bool isInit_ = false;
    bool isOpen_ = false;

    DataBase();
    DataBase(const DataBase& root) = delete;
    DataBase& operator=(const DataBase&) = delete;



public:

    static DataBase& self();

    static void init( const QString& dataBaseName, const QString& hostName, const QString& userName , const QString& userPassword , const QString& dataBaseDriver = "QSQLITE");

    static QStringList table();

    static QSqlDatabase& db();

    static QSqlError open();





};



