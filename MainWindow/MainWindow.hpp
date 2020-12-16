#pragma once

#include <QMainWindow>
#include <QDate>

#include <WidgetAddOrder/WidgetAddOrder.hpp>
#include <WidgetAddProduct/WidgetAddProduct.hpp>
#include <WidgetShowOrder/WidgetShowOrder.hpp>
#include <WidgetProduct/WidgetProduct.hpp>
#include <WidgetShowProducts/WidgetShowProducts.hpp>
#include <WidgetStorage/WidgetStorage.hpp>
#include <WidgetNewImport/WidgetNewImport.hpp>
#include <ShowImportWidget/ShowImportWidget.hpp>
#include <ShowExportWidget.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    WidgetAddProduct* widgetAddProduct_ = nullptr;
    WidgetAddOrder* widgetAddOrder_ = nullptr;
    WidgetShowOrder* widgetShowOrder_ = nullptr;
    WidgetShowProducts* widgetShowProducts_ = nullptr;
    WidgetStorage* widgetStorage_ = nullptr;
    WidgetNewImport* widgetNewImport_ = nullptr;
    ShowImportWidget* showImportWidget_ = nullptr;
    ShowExportWidget* showExportWidget_ = nullptr;

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


    //TODO:rename
    void on_pushButton_clicked();

    //TODO:rename
    void on_pushButton_2_clicked();

    //TODO:rename
    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui = nullptr;
};

