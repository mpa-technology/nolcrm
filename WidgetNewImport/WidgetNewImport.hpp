#pragma once
#include <QWidget>
#include <DataBase/TableProducts.hpp>
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
    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::WidgetNewImport *ui;
};


