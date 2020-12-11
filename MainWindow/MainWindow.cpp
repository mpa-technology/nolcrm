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
    widgetAddProduct_->hide();
    ui->btnAddProduct->setEnabled(true);


    widgetShowOrder_ = new WidgetShowOrder();
    ui->verticalLayout_3->addWidget(widgetShowOrder_);
    widgetShowOrder_->hide();
    ui->btnShowOrder->setEnabled(true);


    widgetAddOrder_ = new WidgetAddOrder();
    ui->verticalLayout_3->addWidget(widgetAddOrder_);
    widgetAddOrder_->hide();
    ui->btnAddOrder->setEnabled(true);


    widgetShowProducts = new WidgetShowProducts();
    ui->verticalLayout_3->addWidget(widgetShowProducts);
    widgetShowProducts->hide();
    ui->pushButton->setEnabled(true);

    widgetStorage = new WidgetStorage();
    ui->verticalLayout_3->addWidget(widgetStorage);
    widgetStorage->hide();
    ui->pushButton_2->setEnabled(true);

    widgetList_.push_back(widgetAddProduct_);
    widgetList_.push_back(widgetAddOrder_);
    widgetList_.push_back(widgetShowOrder_);
    widgetList_.push_back(widgetShowProducts);
    widgetList_.push_back(widgetStorage);

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->showMaximized();

    this->setEnabled(false);

    initModule_();



    this->setEnabled(true);

}

MainWindow::~MainWindow(){
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
    showWidget_(widgetShowProducts);
}


void MainWindow::on_pushButton_2_clicked(){
  showWidget_(widgetStorage);
}

void MainWindow::on_pushButton_3_clicked(){
   showWidget_(nullptr);
}
