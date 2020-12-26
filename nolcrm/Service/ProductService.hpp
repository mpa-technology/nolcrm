/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once

#include <DataBase/TableProducts.hpp>
#include <DataBase/TableStorage.hpp>
#include <Service/GlobalEmitService.hpp>


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

    static void editProduct(const Product& product );

    static void removeProduct(const quint64& id);

    static Product getProductById(const quint64& id);


public slots:
    void gloablCacheClear();


};


