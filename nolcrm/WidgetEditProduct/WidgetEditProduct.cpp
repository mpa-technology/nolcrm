/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#include "WidgetEditProduct.hpp"
#include "ui_WidgetEditProduct.h"

WidgetEditProduct::WidgetEditProduct(const Product& pro) :
    QWidget(nullptr),
    ui(new Ui::WidgetEditProduct)
{
    ui->setupUi(this);

    id = pro.id;
    ui->lineEdit->setText(pro.name);
    ui->lineEdit_2->setText(pro.category);
    ui->doubleSpinBox->setValue(pro.price);
    ui->doubleSpinBox_2->setValue(pro.manufacturerPrice);
    ui->lineEdit_5->setText(pro.manufacturer);
    ui->textEdit->setHtml(pro.descriptions);


}

WidgetEditProduct::~WidgetEditProduct()
{
    delete ui;
}

void WidgetEditProduct::on_pushButton_clicked(){

    Product pro;
    pro.id = id;
    pro.name = ui->lineEdit->text();
    pro.price = ui->doubleSpinBox->value();
    pro.category = ui->lineEdit_2->text();
    pro.descriptions = ui->textEdit->toHtml();
    pro.manufacturer =  ui->lineEdit_5->text();
    pro.manufacturerPrice = ui->doubleSpinBox_2->value();


    //TODO:move to servie

    try {
        TableProducts::editProduct(pro);
                QMessageBox::information(nullptr,tr("Товар"),tr("Товар успешно имзенень"));
    } catch (const retrunDBError& error) {
        QMessageBox::warning(nullptr,tr("Импорт"),tr("Торвр ошыбка имзенень"));
    }



}
