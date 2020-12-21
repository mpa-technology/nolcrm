/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_PRODUCTSERVICE_HPP
#define NOL_CRM_PRODUCTSERVICE_HPP

#include "../DataBase/TableProducts.hpp"
#include "../DataBase/TableStorage.hpp"

class ProductService{
    ProductService();
    ProductService(const ProductService& root) = delete;
    ProductService& operator=(const ProductService&) = delete;


    struct {
        bool isCache = false;
        QVector<Product> list;
    }allProductCache_;


public:


    static ProductService& self();

    bool addProduct( const Product& product);

    static size_t cacheSize(){
        return self().allProductCache_.list.size() * sizeof (Product);
    }


    static  QVector<Product>getAllProduct(){
        auto& th = self();

        if(th.allProductCache_.isCache)
            return th.allProductCache_.list;

        th.allProductCache_.list = TableProducts::getAllProduct();
        th.allProductCache_.isCache = true;

        return th.allProductCache_.list;
    }

};


#endif // NOL_CRM_PRODUCTSERVICE_HPP
