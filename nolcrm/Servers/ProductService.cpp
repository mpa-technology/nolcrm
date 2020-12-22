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

    TableProducts::addProduct(product);

    auto newP = TableProducts::lastProduct();

    TableStorage::addItem(newP.id);



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

void ProductService::editProduct(const Product &product){

    self().allProductCache_.list.clear();
    self().allProductCache_.isCache = false;

    TableProducts::editProduct(product);


}

void ProductService::removeProduct(const quint64 &id){

    TableProducts::removeProduct(id);

    self().allProductCache_.list.clear();
    self().allProductCache_.isCache = false;

}

void ProductService::gloablCacheClear(){

    self().allProductCache_.list.clear();
    self().allProductCache_.isCache = false;
}

