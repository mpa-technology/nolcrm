/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#ifndef NOLCRM_WDGETSTORAGE_HPP
#define NOLCRM_WDGETSTORAGE_HPP

#include <QWidget>
#include "../Servers/GlobalEmitService.hpp"
#include "../Servers/ProductService.hpp"
#include "../DataBase/TableStorageExport.hpp"

namespace Ui {
class WidgetStorage;
}

class WidgetStorage : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetStorage(QWidget *parent = nullptr);
    ~WidgetStorage();


public slots:
void globalUpdate();

private slots:
void on_lineEdit_textChanged(const QString &arg1);



private:
    Ui::WidgetStorage *ui;
};


#endif //NOLCRM_WDGETSTORAGE_HPP
