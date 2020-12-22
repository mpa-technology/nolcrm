/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "WidgetStorage.hpp"
#include "ui_WidgetStorage.h"




WidgetStorage::WidgetStorage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetStorage)
{
    ui->setupUi(this);


    QObject::connect(&GlobalEmitService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));




}

WidgetStorage::~WidgetStorage()
{
    delete ui;
}

void WidgetStorage::globalUpdate(){

    ui->tableWidget->setRowCount(0);



    const auto pro = ProductService::getAllProduct();

    for(const auto& it : pro){

        auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount( row + 1 );

        auto count = TableStorage::getItem(it.id);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(it.name));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(it.category));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(it.manufacturer));
        ui->tableWidget->setItem(row, 3 ,new QTableWidgetItem(QString::number(count.count)));

    }

}

void WidgetStorage::on_lineEdit_textChanged(const QString &arg1){
    Q_UNUSED(arg1);

    auto filter = ui->lineEdit->text();

    int column = ui->comboBox->currentIndex();

    if(filter.isEmpty()){

        for(int i = 0 ; i < ui->tableWidget->rowCount();++i){
            ui->tableWidget->setRowHeight(i,1);

        }
        return;
    }


    for(int i = 0 ; i < ui->tableWidget->rowCount();++i){
        auto item = ui->tableWidget->item(i,column);
        if(item->text().contains(filter)){
            continue;
        }
        ui->tableWidget->setRowHeight(i,0);

    }





}

