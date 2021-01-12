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

    QObject::connect(&GlobalEmitService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));
    ui->tableWidget_2->hideColumn(0);
    ui->dateEdit->setDate(QDate::currentDate());

}

WidgetAddOrder::~WidgetAddOrder()
{
    delete ui;
}

void WidgetAddOrder::show(){




    QWidget::show();

}

void WidgetAddOrder::globalUpdate()
{
    ui->tableWidget_2->setRowCount(0);


    const auto pro = ProductService::getAllProduct();

    for(const auto& it : pro){

        auto row = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->setRowCount( row + 1 );

        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(QString::number(it.id)));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(it.name));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(it.category));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(it.manufacturer));
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(QString::number(it.price)));
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(QString::number(it.manufacturerPrice)));


    }

}

void WidgetAddOrder::on_pushButton_clicked()
{
    auto allPro = ProductService::getAllProduct();
    QVector<QPair<quint64,double>>products;

    for(int i = 0; i != ui->tableWidget->rowCount();++i){
        auto item = ui->tableWidget->item(i,0);
        auto id = item->text().toULong();

        for(auto it : allPro){
            if(it.id == id){
                products.push_back({it.id,it.price});
            }
        }


    }

    if(products.empty()){
        QMessageBox::information(nullptr,tr("Заказ"),"Заказ пуст");
        return;
    }



    try {
        OrderService::addOrder(products,ui->dateEdit->date());
        QMessageBox::information(nullptr,tr("инфо"),tr("Заказ успешн добвалень"));
    } catch (const retrunDBError& error) {
        QMessageBox::warning(nullptr,tr("Error"),error.qstring());
        return;
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

    try {
        ExportService::newExport(stg);
    } catch (const retrunDBError& error) {
        QMessageBox::warning(nullptr,tr("Импорт"),tr("ExportService ошыбка ")+error.what());
    }



    GlobalEmitService::self().emitGlobalUpdate();

}










void WidgetAddOrder::on_pushButton_2_clicked()
{
    auto fileName = QFileDialog::getSaveFileName();
    if(QFileInfo(fileName).suffix().isEmpty())fileName.append(".pdf");


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    //FIXMIX: size A4 printer.setPageSize();
    printer.setOutputFileName(fileName);

   auto ap =  ProductService::getAllProduct();

    QTextDocument doc;
    //FIXMIX: size A4 doc.setPageSize(printer.pageRect().size());
    QString html;


    html.append("<p>Заказ от").append(ui->dateEdit->date().toString()).append("</p>");

    html.append("<table border=1>");
    html.append("<tr>");
    html.append("<th>id</th>");
    html.append("<th>name</th>");
    html.append("<th>man</th>");
    html.append("<th>price</th>");
    html.append("</tr>");
    double sum{0};

    for(auto& it : ap){
    sum += it.price;
    html.append("<tr>");
    html.append("<td>").append(QString::number(it.id)).append("</td>");
    html.append("<td>").append(it.name).append("</td>");
    html.append("<td>").append(it.manufacturer).append("</td>");
    html.append("<td>").append(QString::number(it.manufacturerPrice)).append("</td>");
    html.append("</tr>");

    }
    html.append("</table>");

    html.append("<p>сумма заказа = ").append(QString::number(sum)).append("</p>");

    doc.setHtml(html);
    doc.print(&printer);
}

void WidgetAddOrder::on_tableWidget_2_activated(const QModelIndex &index)
{
    auto pro = TableProducts::self().getProductById(index.siblingAtColumn(0).data().toUInt());

    auto row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row+1);

    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(pro.id)));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(pro.name));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(pro.price)));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(pro.manufacturer));
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(tr("Удалить")));
}

void WidgetAddOrder::on_lineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    auto filter = ui->lineEdit->text();

    int column = ui->comboBox->currentIndex()+1;

    if(filter.isEmpty()){

        for(int i = 0 ; i < ui->tableWidget_2->rowCount();++i){
            ui->tableWidget_2->setRowHeight(i,1);

        }
        return;
    }


    for(int i = 0 ; i < ui->tableWidget_2->rowCount();++i){
        auto item = ui->tableWidget_2->item(i,column);
        if(item->text().contains(filter)){
            continue;
        }
        ui->tableWidget_2->setRowHeight(i,0);

    }
}

void WidgetAddOrder::on_tableWidget_cellActivated(int row, int column)
{

    if(column == 4)
    ui->tableWidget->removeRow(row);
}
