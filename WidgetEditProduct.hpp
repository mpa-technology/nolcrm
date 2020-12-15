#ifndef WIDGETEDITPRODUCT_HPP
#define WIDGETEDITPRODUCT_HPP

#include <QWidget>

namespace Ui {
class WidgetEditProduct;
}

class WidgetEditProduct : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetEditProduct(QWidget *parent = nullptr);
    ~WidgetEditProduct();

private:
    Ui::WidgetEditProduct *ui;
};

#endif // WIDGETEDITPRODUCT_HPP
