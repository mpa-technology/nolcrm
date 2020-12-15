#pragma once
#include <QWidget>
#include <DataBase/TableProducts.hpp>

namespace Ui {
class WidgetEditProduct;
}

class WidgetEditProduct : public QWidget
{
    Q_OBJECT

    quint64 id;

public:
    explicit WidgetEditProduct(const Product& pro);
    ~WidgetEditProduct();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WidgetEditProduct *ui;
};


