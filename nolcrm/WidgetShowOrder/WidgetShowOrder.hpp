/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_WIDGETSHOWORDER_HPP
#define NOLCRM_WIDGETSHOWORDER_HPP


#include <QWidget>

#include "../DataBase/TableProducts.hpp"
#include "../DataBase/TableOrders.hpp"
#include "../Servers/UpdateService.hpp"

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

#endif
