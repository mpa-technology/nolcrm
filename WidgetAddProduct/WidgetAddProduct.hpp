#pragma once
#include <QWidget>
#include <QCloseEvent>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <DataBase/Service.hpp>

namespace Ui {
class WidgetAddProduct;
}

class WidgetAddProduct : public QWidget{

    Q_OBJECT


public:
    explicit WidgetAddProduct(QWidget *parent = nullptr);
    ~WidgetAddProduct();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WidgetAddProduct *ui;

    void closeEvent(QCloseEvent* event);

};


