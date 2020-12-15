#include "WidgetEditProduct.hpp"
#include "ui_WidgetEditProduct.h"

WidgetEditProduct::WidgetEditProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetEditProduct)
{
    ui->setupUi(this);
}

WidgetEditProduct::~WidgetEditProduct()
{
    delete ui;
}
