/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "ReportWidget.hpp"
#include "ui_ReportWidget.h"

QString ReportWidget::rep(const QDate &data){
    QString html;

    double isum = 0;
    double esum = 0;
    double osum = 0;

    double rsum = 0;


    for(auto& it : TableStorageImport::getAllImport()){

        if( it.data.month() != data.month() || it.data.year() != data.year())
            continue;


        isum += it.getSum();
    }

    for(auto& it : ExportService::getAllExport()){
        if( it.data.month() != data.month() || it.data.year() != data.year())
            continue;
        esum += it.getSum();
    }

    for(auto& it : OrderService::getAllOrder()){
        if( it.data.month() != data.month() || it.data.year() != data.year())
            continue;

        osum += it.getSum();


        for( const auto& it : it.products){
            const auto pro =  ProductService::getProductById(it.id);

            rsum +=  pro.price - pro.manufacturerPrice;

        }



    }






    html.append("<p>Отчйт за месяц = ").append(data.toString()).append("</p>");
    html.append("<p>Импорт сумм = ").append(QString::number(isum)).append("</p>");
    html.append("<p>Export сумм = ").append(QString::number(esum)).append("</p>");
    html.append("<p>раница ").append(QString::number(isum - esum)).append("</p>");
    html.append("<p>сумма заказов ").append(QString::number(osum)).append("</p>");
    html.append("<p>чистая сумма заказов ").append(QString::number(rsum)).append("</p>");
    html.append("<p></p>");
    html.append("<p></p>");
    html.append("<p></p>");

    return html;
}

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
    QObject::connect(&GlobalEmitService::self(),SIGNAL(globalUpdate()),this,SLOT(globalUpdate()));


}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::globalUpdate(){

    QString html = rep(QDate::currentDate())+rep(QDate(2020,12,5));



    ui->textBrowser->setHtml(html);
}
