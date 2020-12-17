#ifndef NOLCRM_DATABASE_HPP
#define NOLCRM_DATABASE_HPP

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
    ~DataBase(){
        qDebug()<<"DataBase down";
    }

    static DataBase& self();

    static void init( const QString& dataBaseName, const QString& hostName, const QString& userName , const QString& userPassword , const QString& dataBaseDriver = "QSQLITE");

    static QStringList table();

    static QSqlDatabase& db();

    static QSqlError open();





};



#endif
