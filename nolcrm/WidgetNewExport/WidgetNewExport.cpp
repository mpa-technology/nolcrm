/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "WidgetNewExport.hpp"
#include "ui_WidgetNewExport.h"

void WidgetNewExport::removeCell_(const QModelIndex &index)
{
    qDebug()<<"ok";

    ui->tableWidget_2->removeRow(index.row());

}

WidgetNewExport::WidgetNewExport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewExport)
{
    ui->setupUi(this);
    QObject::connect(&GlobalEmitService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));
}

WidgetNewExport::~WidgetNewExport()
{
    delete ui;
}


void WidgetNewExport::globalUpdate(){

    const auto pro = TableProducts::getAllProduct();
    ui->tableWidget->setRowCount(0);
    for(const auto& it : pro){
        const auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);

        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(it.id)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(it.name));

    }

}

void WidgetNewExport::on_tableWidget_activated(const QModelIndex &index){


    auto item =  ui->tableWidget->item(index.row(),0)->text().toULongLong();

    const auto pro = TableProducts::getProductById(item);

    const auto row = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->setRowCount(row+1);

    ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::number(pro.id)));
    ui->tableWidget_2->setItem(row,1,new QTableWidgetItem(pro.name));
    ui->tableWidget_2->setItem(row,2,new QTableWidgetItem("0"));
    ui->tableWidget_2->setItem(row,3,new QTableWidgetItem(tr("Удалить")));

}

void WidgetNewExport::on_pushButton_clicked()
{
    ExportStorage is;
    is.data = QDate::currentDate();


    for(int i = 0;i!=ui->tableWidget_2->rowCount();++i){
        auto id = ui->tableWidget_2->item(i,0)->text().toULongLong();
        auto count = ui->tableWidget_2->item(i,2)->text().toULongLong();

        ExportStorage::product pro;
        pro.id = id;
        pro.count = count;
        pro.price = TableProducts::getProductById(id).price;
        is.addProduct(pro);
    }


    try {
       ExportService::newExport(is);
       QMessageBox::information(nullptr,tr("Импорт"),tr("export успешно создан"));
       GlobalEmitService::self().emitGlobalUpdate();
    } catch (const retrunDBError& error) {
        QString text;
        text.append(tr("export ошыбка создан")).append(' ').append(error.qstring());
        QMessageBox::warning(nullptr,tr("Импорт"),text);
    }




}

void WidgetNewExport::on_tableWidget_2_activated(const QModelIndex &index)
{
    if(index.column() == 3){
        removeCell_(index);
        return;
    }
}
