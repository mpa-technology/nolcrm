#include "ShowImportWidget.hpp"
#include "ui_ShowImportWidget.h"


ShowImportWidget::ShowImportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowImportWidget){
    ui->setupUi(this);

    QObject::connect(&UpdateService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));

}

ShowImportWidget::~ShowImportWidget(){
    delete ui;
}

void ShowImportWidget::globalUpdate(){

    auto stg = TableStorageImport::getAllImport();
    ui->tableWidget->setRowCount(0);


    for(auto it : stg){

        auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);

        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(it.code)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(it.data.toString()));

    }


}

void ShowImportWidget::on_tableWidget_activated(const QModelIndex &index){


    auto is = TableStorageImport::getImport(ui->tableWidget->item(index.row(),0)->text().toLongLong());

    if(is.code == -1){
        qCritical()<<"is code == -1";
    }


    QString str;
    str.append(QString::number(is.code)).append(is.data.toString()).append("\n");

    for(auto& it : is.products)
        str.append(TableProducts::getProductById(it.id).second.name).append(QString::number(it.count));

    ui->textBrowser->setText(str);


}
