#ifndef NOLCRM_WIDGETSHOWPRODUCTS_HPP
#define NOLCRM_WIDGETSHOWPRODUCTS_HPP

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <WidgetProduct/WidgetProduct.hpp>
#include <WidgetEditProduct/WidgetEditProduct.hpp>

namespace Ui {
class WidgetShowProducts;
}

class WidgetShowProducts : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetShowProducts(QWidget *parent = nullptr);
    ~WidgetShowProducts();

public slots:
    void btd(Product pro);
    void btdr(Product pro);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::WidgetShowProducts *ui;
};

#endif
