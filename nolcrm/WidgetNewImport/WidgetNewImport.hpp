/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#pragma once

#include <QWidget>
#include <QMessageBox>

#include <DataBase/TableProducts.hpp>
#include <DataBase/TableStorageImport.hpp>
#include <Service/GlobalEmitService.hpp>
#include <Service/ImportService.hpp>

namespace Ui {
class WidgetNewImport;
}

class WidgetNewImport : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewImport(QWidget *parent = nullptr);
    ~WidgetNewImport();

private slots:

    void globalUpdate();


    void on_tableProduct_activated(const QModelIndex &index);

    void on_tableNewImportProduct_activated(const QModelIndex &index);

    void on_btnNewImport_clicked();

private:
    Ui::WidgetNewImport *ui;
};

