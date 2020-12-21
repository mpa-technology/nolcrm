/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_PRODUCTSERVICE_HPP
#define NOL_CRM_PRODUCTSERVICE_HPP

#include "../DataBase/TableProducts.hpp"
#include "../DataBase/TableStorage.hpp"
#include "GlobalEmitService.hpp"
class ProductService : public QObject{
    Q_OBJECT

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

    static  QVector<Product>getAllProduct();

public slots:
    void gloablCacheClear();


};


#endif // NOL_CRM_PRODUCTSERVICE_HPP
