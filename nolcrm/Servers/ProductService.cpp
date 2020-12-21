/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "ProductService.hpp"


ProductService::ProductService(){
     QObject::connect(&GlobalEmitService::self(),SIGNAL(gloablCacheClear()),this,SLOT(gloablCacheClear()));
}

ProductService &ProductService::self(){
    static ProductService sig;
    return sig;
}

bool ProductService::addProduct(const Product &product){

    if(!TableProducts::addProduct(product)){
        return  false;
    }
    auto newP = TableProducts::lastProduct();

    if(!TableStorage::addItem(newP.id)){
        return  false;
    }


   self().allProductCache_.list.clear();
   self().allProductCache_.isCache = false;


    return true;
}

QVector<Product> ProductService::getAllProduct(){
    auto& th = self();

    if(th.allProductCache_.isCache)
        return th.allProductCache_.list;

    th.allProductCache_.list = TableProducts::getAllProduct();
    th.allProductCache_.isCache = true;

    return th.allProductCache_.list;
}

void ProductService::gloablCacheClear(){

    self().allProductCache_.list.clear();
    self().allProductCache_.isCache = false;
}

