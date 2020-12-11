#include "WidgetShowOrder/WidgetShowOrder.hpp"
#include "ui_WidgetShowOrder.h"



WidgetShowOrder::WidgetShowOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetShowOrder)
{
    ui->setupUi(this);

    updateTable();

}

WidgetShowOrder::~WidgetShowOrder()
{
    delete ui;
}



void WidgetShowOrder::updateTable(){

    auto ptd = TableOrders::hhgetAllOrder();


    for(const auto& it : ptd){


        auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);

        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(it.code)));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(it.data.toString()));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(it.products.size())));
        ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(it.fpice)+tr("₽")));

    }


}



void WidgetShowOrder::on_tableWidget_activated(const QModelIndex &index)
{
    ui->textBrowser->clear();

    const auto ordId = index.siblingAtColumn(0).data().toULongLong();
    const auto order = TableOrders::hhgetOrderByCode(ordId);

    QString html;

    html += order.data.toString();

    for(const auto& it : order.products){
        auto pro = TableProducts::getProductById(it);

        html += ui->textBrowser->document()->toHtml()+QString("<p>%1</p>").arg("%1").arg(pro.second.name);


    }

    ui->textBrowser->setHtml(html);

}

void WidgetShowOrder::on_pushButton_clicked()
{

    auto code = ui->tableWidget->currentIndex().siblingAtColumn(0).data().toULongLong();
    TableOrders::removeOrderByCode(code);


}
