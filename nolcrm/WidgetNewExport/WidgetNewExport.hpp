/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#ifndef NOLCRM_WIDGETNEWEXPORT_HPP
#define NOLCRM_WIDGETNEWEXPORT_HPP


#include <QWidget>
#include <QMessageBox>

#include "../DataBase/TableProducts.hpp"
#include "../Servers/GlobalEmitService.hpp"
#include "../Servers/ExportService.hpp"

namespace Ui {
class WidgetNewExport;
}

class WidgetNewExport : public QWidget
{
    Q_OBJECT

    void removeCell_(const QModelIndex& index);

public:
    explicit WidgetNewExport(QWidget *parent = nullptr);
    ~WidgetNewExport();

public slots:
    void globalUpdate();



private slots:
    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_tableWidget_2_activated(const QModelIndex &index);

private:
    Ui::WidgetNewExport *ui;
};

#endif //NOLCRM_WIDGETNEWEXPORT_HPP
