/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#ifndef NOLCRM_WDGETSTORAGE_HPP
#define NOLCRM_WDGETSTORAGE_HPP

#include <QWidget>
#include "../Servers/GlobalEmitService.hpp"

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

private:
    Ui::WidgetStorage *ui;
};


#endif
