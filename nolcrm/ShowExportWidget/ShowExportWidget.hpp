/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#pragma once

#include <QWidget>

#include <Service/GlobalEmitService.hpp>
#include <Service/ExportService.hpp>
#include <DataBase/TableProducts.hpp>

namespace Ui {
class ShowExportWidget;
}

class ShowExportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShowExportWidget(QWidget *parent = nullptr);
    ~ShowExportWidget();

public slots:
    void globalUpdate();

private slots:
    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::ShowExportWidget *ui;
};
