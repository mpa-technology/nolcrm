#include "WidgetNewImport.hpp"
#include "ui_WidgetNewImport.h"

WidgetNewImport::WidgetNewImport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNewImport)
{
    ui->setupUi(this);
}

WidgetNewImport::~WidgetNewImport()
{
    delete ui;
}
