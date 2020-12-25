/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once


#include <QWidget>
#include <QMessageBox>

#include <Service/ProductService.hpp>

namespace Ui {
class WidgetEditProduct;
}

class WidgetEditProduct : public QWidget
{
    Q_OBJECT

    quint64 id;

public:
    explicit WidgetEditProduct(const Product& pro);
    ~WidgetEditProduct();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WidgetEditProduct *ui;
};


