#pragma once
#include <QWidget>
#include <QMessageBox>
#include <DataBase/TableProducts.hpp>
#include <DataBase/TableStorageImport.hpp>
#include <DataBase/Service.hpp>

namespace Ui {
class WidgetNewImport;
}

class WidgetNewImport : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewImport(QWidget *parent = nullptr);
    ~WidgetNewImport();

private slots:

    void globalUpdate();

    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::WidgetNewImport *ui;
};


