#ifndef ORDERSERVICE_HPP
#define ORDERSERVICE_HPP


#include "GlobalEmitService.hpp"
#include "../DataBase/TableOrders.hpp"


class OrderService : public QObject{
    Q_OBJECT

    OrderService();
    OrderService(const OrderService& root) = delete;
    OrderService& operator=(const OrderService&) = delete;


    struct {
        bool isCache = false;
        QVector<Order> list;
    }allOrderCache_;

public:

    static OrderService& self();


    static QVector<Order> getAllOrder();

    static bool addOrder(const QVector<QPair<int,double>>& products,const QDate& data = QDate::currentDate());

    static size_t cacheSize();

public slots:
    void gloablCacheClear();

};

#endif // ORDERSERVICE_HPP
