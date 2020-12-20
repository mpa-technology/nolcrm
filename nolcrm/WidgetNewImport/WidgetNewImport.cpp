/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "WidgetNewImport.hpp"
#include "ui_WidgetNewImport.h"


WidgetNewImport::WidgetNewImport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewImport)
{
    ui->setupUi(this);


    QObject::connect(&UpdateService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));





}

WidgetNewImport::~WidgetNewImport()
{
    delete ui;
}

void WidgetNewImport::globalUpdate(){

    const auto pro = TableProducts::getAllProduct();
    ui->tableProduct->setRowCount(0);
    for(const auto& it : pro){
        const auto row = ui->tableProduct->rowCount();
        ui->tableProduct->setRowCount(row+1);

        ui->tableProduct->setItem(row,0,new QTableWidgetItem(QString::number(it.id)));
        ui->tableProduct->setItem(row,1,new QTableWidgetItem(it.name));
        ui->tableProduct->setItem(row,2,new QTableWidgetItem(it.category));
        ui->tableProduct->setItem(row,3,new QTableWidgetItem(it.manufacturer));

    }

}


void WidgetNewImport::on_tableProduct_activated(const QModelIndex &index)
{
    auto item =  ui->tableProduct->item(index.row(),0)->text().toULongLong();

    const auto pro = TableProducts::getProductById(item);

    const auto row = ui->tableNewImportProduct->rowCount();
    ui->tableNewImportProduct->setRowCount(row+1);

    ui->tableNewImportProduct->setItem(row,0,new QTableWidgetItem(QString::number(pro.id)));
    ui->tableNewImportProduct->setItem(row,1,new QTableWidgetItem(pro.name));
    ui->tableNewImportProduct->setItem(row,2,new QTableWidgetItem("0"));
    ui->tableNewImportProduct->setItem(row,3,new QTableWidgetItem(tr("Удалить")));
}

void WidgetNewImport::on_tableNewImportProduct_activated(const QModelIndex &index)
{
    if(index.column() == 3)
        ui->tableNewImportProduct->removeRow(index.row());
}

void WidgetNewImport::on_btnNewImport_clicked()
{
    ImportStorage is;
    is.data = QDate::currentDate();


    for(int i = 0;i!=ui->tableNewImportProduct->rowCount();++i){
        auto id = ui->tableNewImportProduct->item(i,0)->text().toULongLong();
        auto count = ui->tableNewImportProduct->item(i,2)->text().toULongLong();

        ImportStorage::product pro;
        pro.id = id;
        pro.count = count;
        pro.price = TableProducts::getProductById(id).price;
        is.addProduct(pro);
    }


    if(ImportService::newImport(is)){
        QMessageBox::information(nullptr,tr("Импорт"),tr("импорт успешно создан"));
        UpdateService::self().emitGlobalUpdate();
    }
    else
        QMessageBox::warning(nullptr,tr("Импорт"),tr("импорт ошыбка"));
}
