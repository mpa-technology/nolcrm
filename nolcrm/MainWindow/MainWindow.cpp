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
    ui->inlineVerticalLayout->addWidget(widgetAddProduct_);
    ui->btnAddProduct->setEnabled(true);


    widgetShowOrder_ = new WidgetShowOrder();
    ui->inlineVerticalLayout->addWidget(widgetShowOrder_);
    ui->btnShowOrder->setEnabled(true);


    widgetAddOrder_ = new WidgetAddOrder();
    ui->inlineVerticalLayout->addWidget(widgetAddOrder_);
    ui->btnAddOrder->setEnabled(true);


    widgetShowProducts_ = new WidgetShowProducts();
    ui->inlineVerticalLayout->addWidget(widgetShowProducts_);
    ui->btnShowProduct->setEnabled(true);

    widgetStorage_ = new WidgetStorage();
    ui->inlineVerticalLayout->addWidget(widgetStorage_);
    ui->btnShowStorage->setEnabled(true);
    
    
    widgetNewImport_ = new WidgetNewImport();
    ui->inlineVerticalLayout->addWidget(widgetNewImport_);
    ui->btnNewImport->setEnabled(true);
    

    showImportWidget_ = new ShowImportWidget();
    ui->inlineVerticalLayout->addWidget(showImportWidget_);
    ui->btnShowImport->setEnabled(true);


    showExportWidget_ = new ShowExportWidget();
    ui->inlineVerticalLayout->addWidget(showExportWidget_);
    ui->btnShowExport->setEnabled(true);

    widgetNewExport_ = new WidgetNewExport();
    ui->inlineVerticalLayout->addWidget(widgetNewExport_);
    ui->btnNewExport->setEnabled(true);


    reportWidget_ = new ReportWidget();
    ui->inlineVerticalLayout->addWidget(reportWidget_);
    ui->btnShowReport->setEnabled(true);

    widgetList_.push_back(widgetAddProduct_);
    widgetList_.push_back(widgetAddOrder_);
    widgetList_.push_back(widgetShowOrder_);
    widgetList_.push_back(widgetShowProducts_);
    widgetList_.push_back(widgetStorage_);
    widgetList_.push_back(widgetNewImport_);
    widgetList_.push_back(showImportWidget_);
    widgetList_.push_back(showExportWidget_);
    widgetList_.push_back(widgetNewExport_);
    widgetList_.push_back(reportWidget_);



    showWidget_(nullptr);


}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->showMaximized();
    this->setEnabled(false);
    initModule_();
    this->setEnabled(true);







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


void MainWindow::on_btnShowStorage_clicked()
{
      showWidget_(widgetStorage_);
}

void MainWindow::on_btnNewImport_clicked()
{
     showWidget_(widgetNewImport_);
}

void MainWindow::on_btnNewExport_clicked()
{
       showWidget_(widgetNewExport_);
}

void MainWindow::on_btnShowImport_clicked()
{
    showWidget_(showImportWidget_);
}

void MainWindow::on_btnShowExport_clicked()
{
       showWidget_(showExportWidget_);
}

void MainWindow::on_btnShowProduct_clicked()
{
    showWidget_(widgetShowProducts_);
}

void MainWindow::on_btnAbout_clicked()
{
    QString text;
    text.append(tr("Версия программы: ")).append(ProgramService::version()).append('\n');
    text.append(tr("Тип сборки программы: ")).append(ProgramService::buildTypeString()).append('\n');
    text.append(tr("Версия qt: ")).append(QT_VERSION_STR).append('\n');
    text.append(tr("Разработчик: ")).append(tr(R"(ООО"МПА-ТЕХНОЛОДЖЫ")")).append('\n');

    QMessageBox::about(nullptr,"nolcrm",text);
}

void MainWindow::on_btnExit_clicked()
{
        close();
}

void MainWindow::on_btnShowReport_clicked()
{
    showWidget_(reportWidget_);
}
