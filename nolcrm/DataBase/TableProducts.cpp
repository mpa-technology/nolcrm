/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "TableProducts.hpp"
#include "DataBase.hpp"

TableProducts::TableProducts(){}

TableProducts &TableProducts::self(){
    static TableProducts sig;
    return sig;
}

QSqlError TableProducts::lastError(){
    return TableProducts::self().lastError_;
}

void TableProducts::crateTable(){

    if(DataBase::table().contains("products")){
        TableProducts::self().tableCreate_ = true;
        return;
    }

    QSqlQuery query(DataBase::db());


    query.prepare(R"(CREATE TABLE products (
                  Id	INTEGER PRIMARY KEY,
                  Name	TEXT,
                  Category	TEXT,
                  Manufacturer	TEXT,
                  Price	REAL,
                  ManufacturerPrice	REAL,
                  Descriptions TEXT
                  );)");
    query.exec();


    if(query.lastError().type() != QSqlError::NoError){
        qCritical()<<query.lastError();
        TableProducts::self().tableCreate_ = false;
        TableProducts::self().lastError_ = query.lastError();
        throw retrunDBError(query.lastError());
    }

    TableProducts::self().tableCreate_ = true;


}

Product TableProducts::lastProduct(){

    QSqlQuery query(DataBase::db());
    query.prepare("SELECT MAX(Id) FROM products");
    query.exec();
    query.next();
    auto id = query.value(0).toULongLong();
    return TableProducts::getProductById(id);
}

void TableProducts::addProduct(const Product &product){

    QSqlQuery query(DataBase::db());
    query.prepare( R"( INSERT INTO products(Name,Category,Manufacturer,Price,ManufacturerPrice,Descriptions) VALUES(:Name,:Category,:Manufacturer,:Price,:ManufacturerPrice,:Descriptions); )" );
    query.bindValue(":Name",product.name);
    query.bindValue(":Category",product.category);
    query.bindValue(":Manufacturer",product.manufacturer);
    query.bindValue(":Price",product.price);
    query.bindValue(":ManufacturerPrice",product.manufacturerPrice);
    query.bindValue(":Descriptions",product.descriptions);

    query.exec();

    if(query.lastError().type()!=QSqlError::NoError){
        qWarning()<<query.lastError();
       throw retrunDBError(query.lastError());
    }

}



void TableProducts::editProduct(const Product &product){
    QSqlQuery query(DataBase::db());
    query.prepare( R"(UPDATE products SET Name=:Name,Category=:Category,Manufacturer=:Manufacturer,Price=:Price,ManufacturerPrice=:ManufacturerPrice,Descriptions=:Descriptions WHERE Id=:Id )" );
    query.bindValue(":Id",product.id);
    query.bindValue(":Name",product.name);
    query.bindValue(":Category",product.category);
    query.bindValue(":Manufacturer",product.manufacturer);
    query.bindValue(":Price",product.price);
    query.bindValue(":ManufacturerPrice",product.manufacturerPrice);
    query.bindValue(":Descriptions",product.descriptions);

    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qWarning()<<query.lastError();
        throw retrunDBError(query.lastError());
    }



}

TableProducts::productList TableProducts::getAllProduct(){
    productList list;


    QSqlQuery query(DataBase::db());

    query.prepare(R"(SELECT * FROM products )");

    query.exec();
    if(query.lastError().type()!=QSqlError::NoError){
        qWarning()<<query.lastError();
        throw retrunDBError(query.lastError());
    }


    while (query.next()) {

        Product product;
        product.id = query.value("Id").toULongLong();
        product.name = query.value("Name").toString();
        product.category = query.value("Category").toString();
        product.manufacturer = query.value("Manufacturer").toString();
        product.price = query.value("Price").toDouble();
        product.manufacturerPrice = query.value("ManufacturerPrice").toDouble();
        product.descriptions = query.value("Descriptions").toString();
        list.push_back(product);
    }


    return list;
}

Product TableProducts::getProductById(const quint64 &id){
    QSqlQuery query(DataBase::db());



    query.prepare("SELECT * FROM products WHERE Id = :Id;");
    query.bindValue(":Id",id);

    query.exec();

    if( QSqlError error = query.lastError(); error.type() != QSqlError::NoError){
        qWarning()<<error;
        throw retrunDBError(query.lastError());
    }


    query.first();

    Product product;


    product.id = query.value("Id").toUInt();
    product.name = query.value("Name").toString();
    product.manufacturer = query.value("Manufacturer").toString();
    product.price = query.value("Price").toDouble();
    product.manufacturerPrice = query.value("ManufacturerPrice").toDouble();
    product.descriptions = query.value("Descriptions").toString();
    product.category = query.value("Category").toString();



    return product;
}

void TableProducts::removeProduct(const quint64 &id){
    QSqlQuery query;
    query.prepare("DELETE FROM products WHERE Id = :id");
    query.bindValue(":id",id);
    query.exec();

    if(query.lastError().type() != QSqlError::NoError)
        qDebug()<<query.lastError();

    if(query.lastError().type()!=QSqlError::NoError){
        qWarning()<<query.lastError();
        throw retrunDBError(query.lastError());
    }



}
