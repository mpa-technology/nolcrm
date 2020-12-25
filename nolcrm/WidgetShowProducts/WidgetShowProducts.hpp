/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#pragma once

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QTextDocument>
#include <QPrinter>
#include <QFile>
#include <QFileDialog>

#include <Service/GlobalEmitService.hpp>
#include <WidgetEditProduct/WidgetEditProduct.hpp>


namespace Ui {
class WidgetShowProducts;
}

class WidgetShowProducts : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetShowProducts(QWidget *parent = nullptr);
    ~WidgetShowProducts();

public slots:


    void globalUpdate();

private slots:

    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::WidgetShowProducts *ui;
};

