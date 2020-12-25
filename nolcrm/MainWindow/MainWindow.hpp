/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once

#include <QMainWindow>
#include <QDate>

#include <WidgetAddOrder/WidgetAddOrder.hpp>
#include <WidgetAddProduct/WidgetAddProduct.hpp>
#include <WidgetShowOrder/WidgetShowOrder.hpp>
#include <WidgetShowProducts/WidgetShowProducts.hpp>
#include <WidgetStorage/WidgetStorage.hpp>
#include <WidgetNewImport/WidgetNewImport.hpp>
#include <ShowImportWidget/ShowImportWidget.hpp>
#include <ShowExportWidget/ShowExportWidget.hpp>
#include <WidgetNewExport/WidgetNewExport.hpp>
#include <Service/ProgramService.hpp>
#include <DataBase/TableOrders.hpp>
#include <ReportWidget/ReportWidget.hpp>



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
    WidgetNewExport* widgetNewExport_ = nullptr;
    ReportWidget*  reportWidget_ = nullptr;


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


    void on_btnShowStorage_clicked();

    void on_btnNewImport_clicked();

    void on_btnNewExport_clicked();

    void on_btnShowImport_clicked();

    void on_btnShowExport_clicked();

    void on_btnShowProduct_clicked();

    void on_btnAbout_clicked();

    void on_btnExit_clicked();

    void on_btnShowReport_clicked();

private:
    Ui::MainWindow *ui = nullptr;
};

