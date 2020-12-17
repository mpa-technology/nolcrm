/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "ProductService.hpp"


ProductService::ProductService(){}

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



    return true;
}
