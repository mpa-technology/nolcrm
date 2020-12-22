/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_LOGINWIDGET_HPP
#define NOLCRM_LOGINWIDGET_HPP

#include <QWidget>
#include <QFileDialog>
#include "../MainWindow/MainWindow.hpp"
#include "../Settings/Settings.hpp"
#include "../Servers/GlobalService.hpp"


namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LoginWidget *ui;
};


#endif //NOLCRM_LOGINWIDGET_HPP

