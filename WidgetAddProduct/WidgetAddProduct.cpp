#include "WidgetAddProduct.hpp"
#include "ui_WidgetAddProduct.h"

WidgetAddProduct::WidgetAddProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAddProduct)
{
    ui->setupUi(this);




}

WidgetAddProduct::~WidgetAddProduct()
{
    delete ui;
}

void WidgetAddProduct::on_pushButton_clicked()
{
    auto name = ui->lineEdit->text();
    auto category = ui->lineEdit_2->text();
    auto manufacturer = ui->lineEdit_5->text();
    auto price = ui->doubleSpinBox->value();
    auto manufacturerPrice = ui->doubleSpinBox_2->value();
    auto descriptions = ui->textEdit->toHtml();

    Product product;
    product.id = -1;
    product.name = name;
    product.price = price;
    product.category = category;
    product.descriptions = descriptions;
    product.manufacturer = manufacturer;
    product.manufacturerPrice = manufacturerPrice;



    if(ProductService::self().addProduct(product)){
        QMessageBox::information(nullptr,tr("Товар"),tr("Продукт успешн добвалень"));
        UpdateService::self().emitGlobalUpdate();
    }
    else
        QMessageBox::warning(nullptr,tr("Импорт"),tr("Торвр ошыбка "));

}

void WidgetAddProduct::closeEvent(QCloseEvent *event){

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_5->clear();
    ui->doubleSpinBox->clear();
    ui->doubleSpinBox_2->clear();

    event->accept();
}
