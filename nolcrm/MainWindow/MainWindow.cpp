/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#include "MainWindow.hpp"
#include "ui_MainWindow.h"


void MainWindow::showWidget_(QWidget *wgt){

    for(auto* it:widgetList_){
        if(it != wgt)
            it->hide();
        else if(it != nullptr)
            it->show();
    }


}

void MainWindow::initModule_(){

    widgetAddProduct_ = new WidgetAddProduct();
    ui->verticalLayout_3->addWidget(widgetAddProduct_);
    ui->btnAddProduct->setEnabled(true);


    widgetShowOrder_ = new WidgetShowOrder();
    ui->verticalLayout_3->addWidget(widgetShowOrder_);
    ui->btnShowOrder->setEnabled(true);


    widgetAddOrder_ = new WidgetAddOrder();
    ui->verticalLayout_3->addWidget(widgetAddOrder_);
    ui->btnAddOrder->setEnabled(true);


    widgetShowProducts_ = new WidgetShowProducts();
    ui->verticalLayout_3->addWidget(widgetShowProducts_);
    ui->pushButton->setEnabled(true);

    widgetStorage_ = new WidgetStorage();
    ui->verticalLayout_3->addWidget(widgetStorage_);
    ui->pushButton_2->setEnabled(true);
    
    
    widgetNewImport_ = new WidgetNewImport();
    ui->verticalLayout_3->addWidget(widgetNewImport_);
    ui->pushButton_3->setEnabled(true);
    

    showImportWidget_ = new ShowImportWidget();
    ui->verticalLayout_3->addWidget(showImportWidget_);
    ui->pushButton_4->setEnabled(true);


    showExportWidget_ = new ShowExportWidget();
    ui->verticalLayout_3->addWidget(showExportWidget_);
    ui->pushButton_5->setEnabled(true);

    widgetNewExport_ = new WidgetNewExport();
    ui->verticalLayout_3->addWidget(widgetNewExport_);
    ui->pushButton_8->setEnabled(true);

    widgetList_.push_back(widgetAddProduct_);
    widgetList_.push_back(widgetAddOrder_);
    widgetList_.push_back(widgetShowOrder_);
    widgetList_.push_back(widgetShowProducts_);
    widgetList_.push_back(widgetStorage_);
    widgetList_.push_back(widgetNewImport_);
    widgetList_.push_back(showImportWidget_);
    widgetList_.push_back(showExportWidget_);
    widgetList_.push_back(widgetNewExport_);



    showWidget_(nullptr);


}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->showMaximized();
    this->setEnabled(false);
    initModule_();
    this->setEnabled(true);


    //Очйт
    QString html;
    auto data = QDate::currentDate();

    double isum = 0;
    double esum = 0;
    double osum = 0;
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

    for(auto& it : TableOrders::getAllOrder()){
        if( it.data.month() != data.month() || it.data.year() != data.year())
            continue;

       osum += it.getSum();
    }


    html.append("<p>Отчйт за месяц = ").append(data.toString()).append("</p>");
    html.append("<p>Импорт сумм = ").append(QString::number(isum)).append("</p>");
    html.append("<p>Export сумм = ").append(QString::number(esum)).append("</p>");
    html.append("<p>раница ").append(QString::number(isum - esum)).append("</p>");
    html.append("<p>сумма заказов ").append(QString::number(osum)).append("</p>");
    ui->textBrowser->setHtml(html);



}

MainWindow::~MainWindow(){
    qDebug()<<"app shotdown";
    delete ui;
}

void MainWindow::on_btnAddProduct_clicked(){
    showWidget_(widgetAddProduct_);
}

void MainWindow::on_btnAddOrder_clicked(){
    showWidget_(widgetAddOrder_);
}

void MainWindow::on_btnShowOrder_clicked(){
    showWidget_(widgetShowOrder_);
}

void MainWindow::on_pushButton_clicked(){
    showWidget_(widgetShowProducts_);
}


void MainWindow::on_pushButton_2_clicked(){
    showWidget_(widgetStorage_);
}

void MainWindow::on_pushButton_3_clicked(){
    showWidget_(widgetNewImport_);
}

void MainWindow::on_pushButton_6_clicked()
{
    close();
}

void MainWindow::on_pushButton_7_clicked(){   


    QString text;
    text.append(tr("Версия программы: ")).append(ProgramService::version()).append('\n');
    text.append(tr("Тип сборки программы: ")).append(ProgramService::buildTypeString()).append('\n');
    text.append(tr("Версия qt: ")).append(QT_VERSION_STR).append('\n');
    text.append(tr("Разработчик: ")).append(tr(R"(ООО"МПА-ТЕХНОЛОДЖЫ")")).append('\n');

    QMessageBox::about(nullptr,"nolcrm",text);
}

void MainWindow::on_pushButton_4_clicked()
{
    showWidget_(showImportWidget_);
}

void MainWindow::on_pushButton_5_clicked()
{
    showWidget_(showExportWidget_);
}

void MainWindow::on_pushButton_8_clicked()
{
    showWidget_(widgetNewExport_);
}
