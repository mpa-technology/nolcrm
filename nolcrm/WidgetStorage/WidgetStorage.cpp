#include "WidgetStorage.hpp"
#include "ui_WidgetStorage.h"

#include <QSqlTableModel>
#include "../DataBase/Service.hpp"

WidgetStorage::WidgetStorage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetStorage)
{
    ui->setupUi(this);


    QObject::connect(&UpdateService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));




}

WidgetStorage::~WidgetStorage()
{
    delete ui;
}

void WidgetStorage::globalUpdate(){

    ui->tableWidget->setRowCount(0);

    const auto pro = TableProducts::getAllProduct();

    for(const auto& it : pro){

        auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount( row + 1 );

        auto count = TableStorage::getItem(it.id);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(it.name));
        ui->tableWidget->setItem(row, 1 ,new QTableWidgetItem(QString::number(count.count)));

    }

}
