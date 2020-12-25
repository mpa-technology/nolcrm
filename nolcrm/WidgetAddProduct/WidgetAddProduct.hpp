/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once
#include <QWidget>
#include <QCloseEvent>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

#include <Service/GlobalEmitService.hpp>
#include <Service/ProductService.hpp>

namespace Ui {
class WidgetAddProduct;
}

class WidgetAddProduct : public QWidget{

    Q_OBJECT


public:
    explicit WidgetAddProduct(QWidget *parent = nullptr);
    ~WidgetAddProduct();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WidgetAddProduct *ui;

    void closeEvent(QCloseEvent* event);

};

