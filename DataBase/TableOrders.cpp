#include "TableOrders.hpp"
#include "DataBase.hpp"

TableOrders::TableOrders(){}

TableOrders::hordersList TableOrders::hgetAllOrder(){

    QSqlQuery query(DataBase::db());
    query.prepare(R"(SELECT * FROM orders )");
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qWarning()<<query.lastError();
        return {};
    }


    hordersList list;

    while (query.next()) {
        int id =  query.value("Id").toInt();
        int code = query.value("Code").toInt();
        int pid = query.value("ProductsId").toInt();
        double pp = query.value("ProductsPrice").toDouble();
        bool ins = false;


        for(auto&it:list){
            if(it.first==code){
                Orders ord;
                ord.id = id;
                ord.code = code;
                ord.product = {pid,pp};
                it.second.push_back(ord);
                ins = true;
                break;
            }
        }

        if(!ins){
            Orders ord;
            ord.id = id;
            ord.code = code;
            ord.product = {pid,pp};
            list.push_back({code,{ord}});

        }

    }

    return list;
}

QVector<Order> TableOrders::hhgetAllOrder()
{


    QSqlQuery query(DataBase::db());
    query.prepare(R"(SELECT * FROM orders )");
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qWarning()<<query.lastError();
        return {};
    }

    QVector<Order>  list;

    while (query.next()) {


        int id =  query.value("Id").toInt();
        int code = query.value("Code").toInt();
        int pid = query.value("ProductsId").toInt();
        double pp = query.value("ProductsPrice").toDouble();
        QDate data = query.value("Data").toDate();

        bool flag = false;

        for(auto& it : list){

            if(it.code == code){
                it.fpice += pp;
                it.products.push_back(pid);
                it.orders.push_back(id);
                flag = true;
                continue;
            }


        }

        if(flag) continue;

        Order order;
        order.code = code;
        order.fpice = pp;
        order.data = data;
        order.orders.push_back(id);
        order.products.push_back(pid);
        list.push_back(order);
    }


    return list;
}

TableOrders::ordersList TableOrders::getAllOrder(){

    QSqlQuery query(DataBase::db());
    query.prepare(R"(SELECT * FROM orders )");
    query.exec();

    if(query.lastError().type() != QSqlError::NoError){
        qWarning()<<query.lastError();
        return {};
    }


    ordersList list;

    while (query.next()) {
        int id =  query.value("Id").toInt();
        int code = query.value("Code").toInt();
        int pid = query.value("ProductsId").toInt();
        double pp = query.value("ProductsPrice").toDouble();
        Orders ord;
        ord.id = id;
        ord.code = code;
        ord.product = {pid,pp};
        list.push_back(ord);



    }

    return list;
}

QSqlError TableOrders::addOrder(const int &productId, const double &productPrice, const quint64 &code, const QDate &data){

    QSqlQuery query(DataBase::db());
    query.prepare( R"( INSERT INTO orders(Code,ProductsId,ProductsPrice,Data) VALUES(:Code,:ProductsId,:ProductsPrice,:Data); )" );
    query.bindValue(":Code",code);
    query.bindValue(":ProductsId",productId);
    query.bindValue(":ProductsPrice",productPrice);
    query.bindValue(":Data",data);
    query.exec();

    return query.lastError();
}

quint64 TableOrders::findFreeCode_(){

    QSqlQuery query;
    query.prepare("SELECT Code FROM orders");
    query.exec();

    QVector<quint64>codes;

    while (query.next())
        codes.push_back(query.value("Code").toULongLong());


    quint64 code = 1;

    while (codes.indexOf(code)!=-1) {
        code++;
    }


    return code;
}

TableOrders &TableOrders::self(){
    static TableOrders sig;
    return sig;
}

QSqlError TableOrders::lastError(){
    return TableOrders::self().lastError_;
}

bool TableOrders::crateTable(){

    if(DataBase::table().contains("orders")){
        TableOrders::self().tableCreate_ = true;
        return true;
    }

    QSqlQuery query(DataBase::db());


    query.prepare(R"(CREATE TABLE orders(
                  Id	INTEGER PRIMARY KEY,
                  Code	INTEGER,
                  ProductsId INTEGER,
                  ProductsPrice	REAL,
                  Data DATA
                  );)");
    query.exec();


    if(query.lastError().type() != QSqlError::NoError){
        qCritical()<<query.lastError();
        TableOrders::self().tableCreate_ = false;
        TableOrders::self().lastError_ = query.lastError();
        return false;
    }

    TableOrders::self().tableCreate_ = true;

    return true;
}


QSqlError TableOrders::addOrder(QVector<QPair<int, double> > products, const QDate &data){

    auto code = findFreeCode_();

    for(const auto&it:products){
        if( QSqlError error = addOrder(it.first,it.second,code,data); error.type() !=QSqlError::NoError)
            return error;
    }


    return {};
}

QSqlError TableOrders::addOrder(QVector<QPair<int, double> > products, const quint64 &code, const QDate &data){


    for(const auto&it:products){
        if( QSqlError error = addOrder(it.first,it.second,code,data); error.type() !=QSqlError::NoError)
            return error;
    }


    return {};
}

Order TableOrders::hhgetOrderByCode(const quint64 &code){

    for(const auto& it :  hhgetAllOrder())
        if(it.code == code)
            return it;

    return {};
}

QSqlError TableOrders::removeOrderByCode(const quint64 &code){
    QSqlQuery query;
    query.prepare("DELETE FROM orders WHERE Code = :code");
    query.bindValue(":code",code);
    query.exec();

    if(query.lastError().type() != QSqlError::NoError)
        qDebug()<<query.lastError();



    return query.lastError();
}

Order TableOrders::hgetOrderByData(const QDate &data){

    //QSqlQuery query;
    //query.prepare("SELECT * FROM products WHERE Data=:data");
    //query.bindValue(":data",data);

    for(const auto& it : hhgetAllOrder())
        if(it.data == data)
            return it;

    return {};
}

QVector<Order> TableOrders::hgetOrderByData(const int &year, const int &month){

    //QSqlQuery query;
    //query.prepare("SELECT * FROM products WHERE Data=:data");
    //query.bindValue(":data",data);

    QVector<Order> list;

    for(const auto& it : hhgetAllOrder())
        if(it.data.month() == month && it.data.year())
            list.push_back(it);

    return list;
}
