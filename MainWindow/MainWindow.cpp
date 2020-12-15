#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QFuture>


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
    
    widgetList_.push_back(widgetAddProduct_);
    widgetList_.push_back(widgetAddOrder_);
    widgetList_.push_back(widgetShowOrder_);
    widgetList_.push_back(widgetShowProducts_);
    widgetList_.push_back(widgetStorage_);
    widgetList_.push_back(widgetNewImport_);

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

void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox::about(nullptr,"nolcrm","programVersion = 1.0");
}
