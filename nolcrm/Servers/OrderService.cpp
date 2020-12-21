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

bool OrderService::addOrder(const QVector<QPair<int, double> > &products, const QDate &data){

    if(!TableOrders::addOrder(products,data))
        return false;

    self().allOrderCache_.isCache = false;
    self().allOrderCache_.list.clear();


    return true;
}



void OrderService::gloablCacheClear(){
    self().allOrderCache_.isCache = false;
    self().allOrderCache_.list.clear();
}
