#pragma once
#include <QWidget>
#include <DataBase/TableProducts.hpp>
#include <DataBase/TableOrders.hpp>

namespace Ui {
class WidgetShowOrder;
}

class WidgetShowOrder : public QWidget
{
    Q_OBJECT

    void updateTable();

public:
    explicit WidgetShowOrder(QWidget *parent = nullptr);
    ~WidgetShowOrder();



private slots:

    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::WidgetShowOrder *ui;
};


