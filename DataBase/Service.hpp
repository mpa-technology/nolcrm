#pragma once
#include <exception>
#include <stdexcept>
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
