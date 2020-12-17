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
    ui->tableWidget->setRowCount(0);
    for(const auto& it : pro){
        const auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);

        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(it.id)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(it.name));

    }

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


    if(ImportService::newImport(is)){
        QMessageBox::information(nullptr,tr("Импорт"),tr("импорт успешно создан"));
        UpdateService::self().emitGlobalUpdate();
    }
    else
        QMessageBox::warning(nullptr,tr("Импорт"),tr("импорт ошыбка создан"));

}
