/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "ShowImportWidget.hpp"
#include "ui_ShowImportWidget.h"


ShowImportWidget::ShowImportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowImportWidget){
    ui->setupUi(this);

    QObject::connect(&GlobalEmitService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));

}

ShowImportWidget::~ShowImportWidget(){
    delete ui;
}
#include "../Service/GlobalService.hpp"
void ShowImportWidget::globalUpdate(){


    auto stg = ImportService::getAllImport();
    ui->tableWidget->setRowCount(0);


    for(auto it : stg){

        auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);

        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(it.code)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(it.data.toString()));

    }


}

void ShowImportWidget::on_tableWidget_activated(const QModelIndex &index){


    auto is = TableStorageImport::getImport(ui->tableWidget->item(index.row(),0)->text().toULong());




    QString html;

    html.append("<p>").append(QString::number(is.code)).append(is.data.toString()).append("</p>");
    html.append("<p>").append(QString::number(is.getSum())).append("</p>");
    for(auto& it : is.products){
        html.append("<p>").append(TableProducts::getProductById(it.id).name).append("</p>");
        html.append("<p>").append(QString::number(it.count)).append("</p>");

    }


    ui->textBrowser->setHtml(html);


}

void ShowImportWidget::on_pushButton_clicked()
{

    auto code = ui->tableWidget->currentIndex().siblingAtColumn(0).data().toULongLong();
    ImportService::removeImportByCode(code);
}
