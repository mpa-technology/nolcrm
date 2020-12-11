#pragma once
#include <QWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <DataBase/TableProducts.hpp>
#include <DataBase/TableOrders.hpp>
#include <WidgetProduct/WidgetProduct.hpp>

namespace Ui {
class WidgetAddOrder;
}

class WidgetAddOrder : public QWidget
{
    Q_OBJECT




public:
    explicit WidgetAddOrder(QWidget *parent = nullptr);
    ~WidgetAddOrder();

    void show();


private slots:

    void on_pushButton_clicked();
    void btd(Product pro);


private:
    Ui::WidgetAddOrder *ui;


    void closeEvent(QCloseEvent* event);

};


