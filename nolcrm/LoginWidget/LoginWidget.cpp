/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "LoginWidget.hpp"
#include "ui_LoginWidget.h"



LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);


}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_pushButton_clicked()
{


    if(ui->radioButton->isChecked()){
        auto& settings = Settings::self();
        auto fileName = ui->lineEdit->text();

        if(QFileInfo(fileName).suffix().isEmpty())fileName.append(".db");

        settings.setValue("database/name",fileName);
        settings.setValue("database/hostName","@CLEAR");
        settings.setValue("database/userName","@CLEAR");
        settings.setValue("database/userPassword","@CLEAR");
        settings.setValue("database/port","@CLEAR");
        settings.setValue("database/driver","QSQLITE");
        if(!GlobalService::waekup()){
            QMessageBox::warning(nullptr,"error","error");
            return;
        }

    }


     MainWindow* w = new MainWindow();
     w->show();
     close();

}

void LoginWidget::on_pushButton_2_clicked()
{
    auto fileName = QFileDialog::getSaveFileName();
    if(QFileInfo(fileName).suffix().isEmpty())fileName.append(".db");

    ui->lineEdit->setText(fileName);

}
