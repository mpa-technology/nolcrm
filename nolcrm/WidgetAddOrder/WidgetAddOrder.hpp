/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_WIDGETADDORDER_HPP
#define NOLCRM_WIDGETADDORDER_HPP


#include <QWidget>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>


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

#endif //NOLCRM_WIDGETADDORDER_HPP
