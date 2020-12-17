#ifndef NOLCRM_SERVICE_HPP
#define NOLCRM_SERVICE_HPP


#include <exception>
#include <stdexcept>
#include <Settings/Settings.hpp>
#include "DataBase.hpp"
#include "TableOrders.hpp"
#include "TableProducts.hpp"
#include "TableStorage.hpp"
#include "TableStorageImport.hpp"

#define NOLCRM_CRM_DEBUG
class ProgramService{

public:

    static QString version(){
        return "1.2.0";
    }

    static QString name(){
        return "nolcrm";
    }

};


class GlobalService{

    GlobalService();
    GlobalService(const GlobalService& root) = delete;
    GlobalService& operator=(const GlobalService&) = delete;

    bool initDataBase_();


public:

    ~GlobalService(){
        qDebug()<<"GlobalService down";
    }

    static GlobalService& self();


    static  bool waekup();


    void initTableBase();


};


class UpdateService : public QObject{
    Q_OBJECT

public:

    static UpdateService& self(){
        static UpdateService sig;
        return sig;
    }

    void emitGlobalUpdate(){
        qDebug()<<"emit globalUpdate";
        emit globalUpdate();
    }

signals:
void globalUpdate();



};


class ProductService{
    ProductService(){}
    ProductService(const ProductService& root) = delete;
    ProductService& operator=(const ProductService&) = delete;

public:


    static ProductService& self(){
        static ProductService sig;
        return sig;
    }

    bool addProduct( const Product& product){

       if(auto sqlerror = TableProducts::addProduct(product).type(); sqlerror != QSqlError::NoError){
           qWarning()<<sqlerror;
           return  false;
       }
        auto newP = TableProducts::lastProduct();

        if(auto sqlerror = TableStorage::addItem(newP.id).type(); sqlerror != QSqlError::NoError){
            qWarning()<<sqlerror;
            return  false;
        }



        return true;
    }


};

class ImportService{
    ImportService(){}
    ImportService(const ImportService& root) = delete;
    ImportService& operator=(const ImportService&) = delete;

public:

    static ImportService& self(){
        static ImportService sig;
        return sig;
    }

    static  bool newImport ( const ImportStorage& is){

        if(!TableStorageImport::newImport(is)){
            return false;
        }

        for(auto it2 : is.products){
            if(!TableStorage::addCount(it2.id,it2.count))
                return false;
        }


        return true;
    }


};


class ExportService{
    ExportService(){}
    ExportService(const ExportService& root) = delete;
    ExportService& operator=(const ExportService&) = delete;

public:

    static ExportService& self(){
        static ExportService sig;
        return sig;
    }

    static  bool newExport( const ImportStorage& is){


        if(!TableStorageExport::newExport(is)){
            return false;
        }

        for(auto it2 : is.products){
            if(!TableStorage::subCount(it2.id,it2.count))
                return false;
        }


        return true;
    }


};

#endif
