/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#include "WidgetProduct.hpp"
#include "ui_WidgetProduct.h"

WidgetProduct::WidgetProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetProduct)
{
    ui->setupUi(this);


    ui->btnLeft->hide();
    ui->btnRight->hide();
}

WidgetProduct::~WidgetProduct()
{

    delete ui;
}

void WidgetProduct::setProduct(const Product &product){

    ui->lblName->setText(product.name);
    ui->lblManufacturer->setText(product.manufacturer);
    ui->lblPrice->setText(QString::number(product.price)+tr("₽"));
    product_ = product;

}

void WidgetProduct::setButtonLeft(const QString &text){
 ui->btnLeft->setText(text);
 ui->btnLeft->show();
}

void WidgetProduct::setButtonRight(const QString &text)
{
   ui->btnRight->setText(text);
   ui->btnRight->show();
}



void WidgetProduct::on_btnLeft_clicked()
{
    emit leftBtnClicked(product_);
}

void WidgetProduct::on_btnRight_clicked()
{
    emit rightBtnClicked(product_);
}
