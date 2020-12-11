#pragma once

#include <QMainWindow>
#include <QDate>

#include <WidgetAddOrder/WidgetAddOrder.hpp>
#include <WidgetAddProduct/WidgetAddProduct.hpp>
#include <WidgetShowOrder/WidgetShowOrder.hpp>
#include <WidgetProduct/WidgetProduct.hpp>
#include <WidgetShowProducts/WidgetShowProducts.hpp>
#include <WidgetStorage/WidgetStorage.hpp>
#include <DataBase/TableOrders.hpp>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    WidgetAddProduct* widgetAddProduct_ = nullptr;
    WidgetAddOrder* widgetAddOrder_ = nullptr;
    WidgetShowOrder* widgetShowOrder_ = nullptr;
    WidgetShowProducts* widgetShowProducts = nullptr;
    WidgetStorage* widgetStorage = nullptr;

    QVector<QWidget*>widgetList_;

    void showWidget_(QWidget* wgt);


    void initModule_();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_btnAddProduct_clicked();

    void on_btnAddOrder_clicked();

    void on_btnShowOrder_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui = nullptr;
};

