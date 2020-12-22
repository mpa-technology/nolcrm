/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "WidgetShowProducts.hpp"
#include "ui_WidgetShowProducts.h"


#include <utility>

WidgetShowProducts::WidgetShowProducts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetShowProducts)
{
    ui->setupUi(this);

    QObject::connect(&GlobalEmitService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));

    ui->tableWidget->hideColumn(0);

}

WidgetShowProducts::~WidgetShowProducts()
{
    delete ui;
}





void WidgetShowProducts::globalUpdate(){

    ui->tableWidget->setRowCount(0);


    const auto pro = ProductService::getAllProduct();

    for(const auto& it : pro){

        auto row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount( row + 1 );

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(it.id)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(it.name));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(it.category));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(it.manufacturer));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(it.price)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(it.manufacturerPrice)));


    }


}



void WidgetShowProducts::on_pushButton_clicked()
{
    auto fileName = QFileDialog::getSaveFileName();
    if(QFileInfo(fileName).suffix().isEmpty())fileName.append(".pdf");


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

   auto ap =  TableProducts::getAllProduct();

    QTextDocument doc;
    doc.setPageSize(printer.pageRect().size());
    QString html;


    html.append("<table border=1>");
    html.append("<tr>");
    html.append("<th>id</th>");
    html.append("<th>name</th>");
    html.append("<th>man</th>");
    html.append("<th>price</th>");
    html.append("</tr>");

    for(auto& it : ap){

    html.append("<tr>");
    html.append("<td>").append(QString::number(it.id)).append("</td>");
    html.append("<td>").append(it.name).append("</td>");
    html.append("<td>").append(it.manufacturer).append("</td>");
    html.append("<td>").append(QString::number(it.manufacturerPrice)).append("</td>");
    html.append("</tr>");

    }
    html.append("</table>");

    doc.setHtml(html);
    doc.print(&printer);
}

void WidgetShowProducts::on_lineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    auto filter = ui->lineEdit->text();

    int column = ui->comboBox->currentIndex()+1;

    if(filter.isEmpty()){

        for(int i = 0 ; i < ui->tableWidget->rowCount();++i){
            ui->tableWidget->setRowHeight(i,1);

        }
        return;
    }


    for(int i = 0 ; i < ui->tableWidget->rowCount();++i){
        auto item = ui->tableWidget->item(i,column);
        if(item->text().contains(filter)){
            continue;
        }
        ui->tableWidget->setRowHeight(i,0);

    }




}

void WidgetShowProducts::on_pushButton_3_clicked()
{

    quint64 id = ui->tableWidget->currentIndex().siblingAtColumn(0).data().toUInt();

    (new WidgetEditProduct(TableProducts::getProductById(id)))->show();
}

void WidgetShowProducts::on_pushButton_2_clicked(){

    QMessageBox msg;


    msg.addButton(QMessageBox::StandardButton::Yes);
    msg.addButton(QMessageBox::StandardButton::No);
    msg.setText(tr("Вы хотите удалитьт товар"));

    if(msg.exec() == QMessageBox::No)
        return;



    quint64 id = ui->tableWidget->currentIndex().siblingAtColumn(0).data().toUInt();
    ProductService::removeProduct(id);

    GlobalEmitService::emitGlobalUpdate();

}
