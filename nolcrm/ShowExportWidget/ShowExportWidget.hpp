/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_SHOWEXPORTWIDGET_HPP
#define NOLCRM_SHOWEXPORTWIDGET_HPP


#include <QWidget>

#include "../Servers/GlobalEmitService.hpp"
#include "../Servers/ExportService.hpp"
#include "../DataBase/TableProducts.hpp"

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

private:
    Ui::ShowExportWidget *ui;
};

#endif
