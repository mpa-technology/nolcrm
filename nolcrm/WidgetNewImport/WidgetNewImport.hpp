/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#ifndef NOLCRM_WIDGETNEWIMPORT_HPP
#define NOLCRM_WIDGETNEWIMPORT_HPP


#include <QWidget>
#include <QMessageBox>

#include "../DataBase/TableProducts.hpp"
#include "../DataBase/TableStorageImport.hpp"
#include "../Servers/UpdateService.hpp"
#include "../Servers/ImportService.hpp"

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

    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::WidgetNewImport *ui;
};

#endif
