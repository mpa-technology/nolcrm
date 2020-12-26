/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once


#include <QWidget>
#include <QDate>
#include <Service/GlobalEmitService.hpp>
#include <Service/ExportService.hpp>
#include <Service/ImportService.hpp>
#include <Service/OrderService.hpp>
#include <Service/ProductService.hpp>


namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWidget(QWidget *parent = nullptr);
    ~ReportWidget();

public slots:
    void globalUpdate();


private:
    Ui::ReportWidget *ui;
};

