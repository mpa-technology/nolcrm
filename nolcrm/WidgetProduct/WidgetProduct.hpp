#ifndef NOLCRM_WIDGETPRODUCT_HPP
#define NOLCRM_WIDGETPRODUCT_HPP

#include <QWidget>
#include <DataBase/TableProducts.hpp>

namespace Ui {
class WidgetProduct;
}

class WidgetProduct : public QWidget
{
    Q_OBJECT

    Product product_;


public:
    explicit WidgetProduct(QWidget *parent = nullptr);
    ~WidgetProduct();

    void setProduct(const Product& product);

    void setButtonLeft(const QString& text);

    void setButtonRight(const QString& text);

signals:
void leftBtnClicked(Product);
void rightBtnClicked(Product);

private slots:


    void on_btnLeft_clicked();

    void on_btnRight_clicked();

private:
    Ui::WidgetProduct *ui;
};

#endif
