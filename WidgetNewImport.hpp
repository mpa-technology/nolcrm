#ifndef WIDGETNEWIMPORT_HPP
#define WIDGETNEWIMPORT_HPP

#include <QWidget>

namespace Ui {
class WidgetNewImport;
}

class WidgetNewImport : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewImport(QWidget *parent = nullptr);
    ~WidgetNewImport();

private:
    Ui::WidgetNewImport *ui;
};

#endif // WIDGETNEWIMPORT_HPP
