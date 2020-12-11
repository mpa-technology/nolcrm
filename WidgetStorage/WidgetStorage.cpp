#include "WidgetStorage.hpp"
#include "ui_WidgetStorage.h"

#include <QSqlTableModel>


WidgetStorage::WidgetStorage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetStorage)
{
    ui->setupUi(this);





}

WidgetStorage::~WidgetStorage()
{
    delete ui;
}
