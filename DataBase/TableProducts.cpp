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

bool TableProducts::crateTable(){

    if(DataBase::table().contains("products")){
        TableProducts::self().tableCreate_ = true;
        return true;
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
        return false;
    }

    TableProducts::self().tableCreate_ = true;

    return true;
}

QSqlError TableProducts::addProduct(const Product &product){

    return addProduct(product.name,product.category,product.manufacturer,product.price,product.manufacturerPrice,product.descriptions);
}

QSqlError TableProducts::addProduct(const QString &name, const QString &category, const QString &manufacturer, const double &price, const double &manufacturerPrice, const QString &descriptions){
    QSqlQuery query(DataBase::db());
    query.prepare( R"( INSERT INTO products(Name,Category,Manufacturer,Price,ManufacturerPrice,Descriptions) VALUES(:Name,:Category,:Manufacturer,:Price,:ManufacturerPrice,:Descriptions); )" );
    query.bindValue(":Name",name);
    query.bindValue(":Category",category);
    query.bindValue(":Manufacturer",manufacturer);
    query.bindValue(":Price",price);
    query.bindValue(":ManufacturerPrice",manufacturerPrice);
    query.bindValue(":Descriptions",descriptions);

    query.exec();


    return query.lastError();
}

bool TableProducts::editProduct(const Product &product){
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
        return false;
    }


    return true;
}

TableProducts::productList TableProducts::getAllProduct(){
    productList list;


    QSqlQuery query(DataBase::db());

    query.prepare(R"(SELECT * FROM products )");

    query.exec();
    if(query.lastError().type()!=QSqlError::NoError){
        qWarning()<<query.lastError();
        return {};
    }


    while (query.next()) {

        Product product;
        product.id = query.value("Id").toInt();
        product.name = query.value("Name").toString();
        product.manufacturer = query.value("Manufacturer").toString();
        product.price = query.value("Price").toDouble();
        product.manufacturerPrice = query.value("ManufacturerPrice").toDouble();
        product.descriptions = query.value("Descriptions").toString();
        list.push_back(product);
    }


    return list;
}

QPair<QSqlError, Product> TableProducts::getProductById(const quint64 &id){
    QSqlQuery query(DataBase::db());



    query.prepare("SELECT * FROM products WHERE Id = :Id;");
    query.bindValue(":Id",id);

    query.exec();

    if( QSqlError error = query.lastError(); error.type() != QSqlError::NoError){
        qWarning()<<error;
        return {};
    }


    query.first();

    Product product;


    product.id = query.value("Id").toInt();
    product.name = query.value("Name").toString();
    product.manufacturer = query.value("Manufacturer").toString();
    product.price = query.value("Price").toDouble();
    product.manufacturerPrice = query.value("ManufacturerPrice").toDouble();
    product.descriptions = query.value("Descriptions").toString();

    return {query.lastError(),product};
}

QSqlError TableProducts::removeProduct(const quint64 &id){
    QSqlQuery query;
    query.prepare("DELETE FROM products WHERE Id = :id");
    query.bindValue(":id",id);
    query.exec();

    if(query.lastError().type() != QSqlError::NoError)
        qDebug()<<query.lastError();

    return query.lastError();
}