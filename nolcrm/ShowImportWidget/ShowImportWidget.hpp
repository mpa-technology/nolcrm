/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once


#include <QWidget>
#include <Service/GlobalEmitService.hpp>
#include <DataBase/TableProducts.hpp>
#include <Service/ImportService.hpp>

namespace Ui {
class ShowImportWidget;
}

class ShowImportWidget : public QWidget
{
    Q_OBJECT




public:
    explicit ShowImportWidget(QWidget *parent = nullptr);
    ~ShowImportWidget();


public slots:
void globalUpdate();

private slots:
void on_tableWidget_activated(const QModelIndex &index);

void on_pushButton_clicked();

private:
    Ui::ShowImportWidget *ui;
};


