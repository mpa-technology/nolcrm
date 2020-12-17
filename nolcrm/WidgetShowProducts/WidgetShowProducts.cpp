/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "WidgetShowProducts.hpp"
#include "ui_WidgetShowProducts.h"




WidgetShowProducts::WidgetShowProducts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetShowProducts)
{
    ui->setupUi(this);

    QObject::connect(&UpdateService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));


}

WidgetShowProducts::~WidgetShowProducts()
{
    delete ui;
}

void WidgetShowProducts::btd(Product pro)
{

QMessageBox msg;


msg.addButton(QMessageBox::StandardButton::Yes);
msg.addButton(QMessageBox::StandardButton::No);
msg.setText(tr("Вы хотите удалитьт товар"));

if(msg.exec() == QMessageBox::No)
    return;

TableProducts::removeProduct(pro.id);



}

void WidgetShowProducts::btdr(Product pro){

  auto ptr =  new WidgetEditProduct(pro);
  ptr->show();


}

void WidgetShowProducts::globalUpdate()
{

    QLayoutItem* wgt;

    while ((wgt = ui->verticalLayout_fs->takeAt(0))!=0 ) {
        delete wgt;
    }



    for(const auto& it : TableProducts::getAllProduct()){
        auto* item = new WidgetProduct();
        item->setProduct(it);
        item->setButtonLeft(tr("Удалить"));
        item->setButtonRight(tr("Изминить"));
        QObject::connect(item,SIGNAL(leftBtnClicked(Product)),this,SLOT(btd(Product)));
        QObject::connect(item,SIGNAL(rightBtnClicked(Product)),this,SLOT(btdr(Product)));
        ui->verticalLayout_fs->addWidget(item);
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