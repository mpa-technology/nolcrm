/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#include "WidgetAddOrder/WidgetAddOrder.hpp"
#include "ui_WidgetAddOrder.h"


WidgetAddOrder::WidgetAddOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAddOrder)
{
    ui->setupUi(this);


    ui->dateEdit->setDate(QDate::currentDate());




    for(const auto& it : ProductService::getAllProduct()){
        auto* item = new WidgetProduct();
        item->setProduct(it);
        item->setButtonLeft("add");
        QObject::connect(item,SIGNAL(leftBtnClicked(Product)),this,SLOT(btd(Product)));

        ui->verticalLayout_4->addWidget(item);
    }



}

WidgetAddOrder::~WidgetAddOrder()
{
    delete ui;
}

void WidgetAddOrder::show(){




    QWidget::show();

}

void WidgetAddOrder::on_pushButton_clicked()
{
    auto allPro = ProductService::getAllProduct();
    QVector<QPair<int,double>>products;

    for(int i = 0; i != ui->tableWidget->rowCount();++i){
        auto item = ui->tableWidget->item(i,0);
        int x = item->text().toInt();

        for(auto it : allPro){
            if(it.id==x){
                products.push_back({it.id,it.price});
            }
        }


    }

    if(products.empty()){
        QMessageBox::information(nullptr,tr("Заказ"),"Заказ пуст");
        return;
    }




    if(!OrderService::addOrder(products,ui->dateEdit->date())){
        QMessageBox::warning(nullptr,tr("Error"),"error");
        return;
    }else{
        QMessageBox::information(nullptr,tr("инфо"),tr("Заказ успешн добвалень"));
    }


    if(!ui->checkBox->isChecked())
        return;

    ExportStorage stg;
    stg.data = ui->dateEdit->date();


    for(auto it : products){
        ExportStorage::product pro;
        pro.id = it.first;
        pro.count = 1;
        pro.price = it.second;
        stg.addProduct(pro);
    }


    if(!ExportService::newExport(stg))
        QMessageBox::warning(nullptr,tr("Импорт"),tr("ExportService ошыбка "));


    GlobalEmitService::self().emitGlobalUpdate();

}








void WidgetAddOrder::btd(Product pro)
{

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row+1);

    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(pro.id)));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(pro.name));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(pro.price)));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(pro.manufacturer));
}
