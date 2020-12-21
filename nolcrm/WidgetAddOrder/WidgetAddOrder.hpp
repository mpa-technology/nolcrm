/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_WIDGETADDORDER_HPP
#define NOLCRM_WIDGETADDORDER_HPP


#include <QWidget>
#include <QMessageBox>

#include "../WidgetProduct/WidgetProduct.hpp"
#include "../Servers/GlobalEmitService.hpp"
#include "../Servers/ExportService.hpp"
#include "../DataBase/TableOrders.hpp"
#include "../Servers/ProductService.hpp"
#include "../Servers/OrderService.hpp"
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



};

#endif
