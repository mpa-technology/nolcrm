#pragma once
#include <exception>
#include <stdexcept>
#include <Settings/Settings.hpp>
#include "DataBase.hpp"
#include "TableOrders.hpp"
#include "TableProducts.hpp"
#include "TableStorage.hpp"
#include "TableStorageImport.hpp"


class GlobalService{

    GlobalService();
    GlobalService(const GlobalService& root) = delete;
    GlobalService& operator=(const GlobalService&) = delete;

    bool initDataBase_();


public:

    static GlobalService& self();


    static  bool waekup(){
        try {
            GlobalService::self().initTableBase();
        } catch (const std::exception& exp) {
            qCritical()<<exp.what();
            return false;
        }

        return true;
    }


    void initTableBase();


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

    void addProduct( const Product& product){

        TableProducts::addProduct(product);
        auto newP = TableProducts::lastProduct();
        TableStorage::addItem(newP.id);


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

