/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#pragma once

#include <QWidget>

#include <DataBase/TableProducts.hpp>
#include <DataBase/TableOrders.hpp>
#include <Service/GlobalEmitService.hpp>

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

public slots:

    void globalUpdate();

private slots:

    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::WidgetShowOrder *ui;
};
