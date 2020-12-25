/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#pragma once

#include <QWidget>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>


#include <Service/GlobalEmitService.hpp>
#include <Service/ExportService.hpp>
#include <DataBase/TableOrders.hpp>
#include <Service/ProductService.hpp>
#include <Service/OrderService.hpp>

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


public slots:


    void globalUpdate();


private slots:


    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

    void on_tableWidget_2_activated(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableWidget_cellActivated(int row, int column);

private:
    Ui::WidgetAddOrder *ui;



};
