#include "WidgetNewImport.hpp"
#include "ui_WidgetNewImport.h"

#include <DataBase/TableStorageImport.hpp>
#include <DataBase/Service.hpp>

WidgetNewImport::WidgetNewImport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewImport)
{
    ui->setupUi(this);

    const auto pro = TableProducts::getAllProduct();

    for(const auto& it : pro){
        const auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);

        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(it.id)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(it.name));

    }




}

WidgetNewImport::~WidgetNewImport()
{
    delete ui;
}

void WidgetNewImport::on_tableWidget_activated(const QModelIndex &index){
    auto item =  ui->tableWidget->item(index.row(),0)->text().toULongLong();

    const auto pro = TableProducts::getProductById(item).second;

    const auto row = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->setRowCount(row+1);

    ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::number(pro.id)));
    ui->tableWidget_2->setItem(row,1,new QTableWidgetItem(pro.name));
    ui->tableWidget_2->setItem(row,2,new QTableWidgetItem("0"));

}

void WidgetNewImport::on_pushButton_clicked(){

    ImportStorage is;
    is.data = QDate::currentDate();


    for(int i = 0;i!=ui->tableWidget_2->rowCount();++i){
        auto id = ui->tableWidget_2->item(i,0)->text().toULongLong();
        auto count = ui->tableWidget_2->item(i,2)->text().toULongLong();

        ImportStorage::product pro;
        pro.id = id;
        pro.count = count;
        pro.price = TableProducts::getProductById(id).second.price;
        is.addProduct(pro);
    }


   qDebug()<<ImportService::newImport(is);

}
