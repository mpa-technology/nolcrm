#include "OrderService.hpp"

OrderService::OrderService()
{
    QObject::connect(&GlobalEmitService::self(),SIGNAL(gloablCacheClear()),this,SLOT(gloablCacheClear()));

}

OrderService &OrderService::self(){
    static OrderService sig;
    return sig;
}

QVector<Order> OrderService::getAllOrder(){
    auto& sf =self();
    if(sf.allOrderCache_.isCache)
        return sf.allOrderCache_.list;

    self().allOrderCache_.isCache = true;
    self().allOrderCache_.list = TableOrders::getAllOrder();


    return sf.allOrderCache_.list;
}

void OrderService::addOrder(const QVector<QPair<quint64, double> > &products, const QDate &data){

    TableOrders::addOrder(products,data);


    self().allOrderCache_.isCache = false;
    self().allOrderCache_.list.clear();
}



void OrderService::gloablCacheClear(){
    self().allOrderCache_.isCache = false;
    self().allOrderCache_.list.clear();
}
