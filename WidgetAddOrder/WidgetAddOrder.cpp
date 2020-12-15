#include "WidgetAddOrder/WidgetAddOrder.hpp"
#include "ui_WidgetAddOrder.h"


WidgetAddOrder::WidgetAddOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAddOrder)
{
    ui->setupUi(this);


    ui->dateEdit->setDate(QDate::currentDate());




    for(const auto& it : TableProducts::getAllProduct()){
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
    auto allPro = TableProducts::getAllProduct();
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




  //ExportService::newExport()


    if( QSqlError error =  TableOrders::addOrder(products,ui->dateEdit->date());error.type() != error.NoError){
        QMessageBox::warning(nullptr,tr("Error"),error.text());
        return;
    }else{
        QMessageBox::information(nullptr,tr("инфо"),tr("Заказ успешн добвалень"));
    }


    if(!ui->checkBox->isChecked())
        return;

    ImportStorage stg;
    stg.data = ui->dateEdit->date();


    for(auto it : products){
        ImportStorage::product pro;
        pro.id = it.first;
        pro.count = 1;
        pro.price = it.second;
        stg.addProduct(pro);
    }

   qDebug()<< ExportService::newExport(stg);

}



void WidgetAddOrder::closeEvent(QCloseEvent *event){
    ui->tableWidget->setRowCount(0);


    event->accept();
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
