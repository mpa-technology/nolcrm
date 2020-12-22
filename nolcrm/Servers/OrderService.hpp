#ifndef NOL_CRM_ORDERSERVICE_HPP
#define NOL_CRM_ORDERSERVICE_HPP


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

    static void addOrder(const QVector<QPair<quint64,double>>& products,const QDate& data = QDate::currentDate());



public slots:
    void gloablCacheClear();

};

#endif // NOL_CRM_ORDERSERVICE_HPP
