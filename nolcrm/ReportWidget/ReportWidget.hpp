#ifndef REPORTWIDGET_HPP
#define REPORTWIDGET_HPP

#include <QWidget>
#include <QDate>
#include "../Servers/GlobalEmitService.hpp"
#include "../Servers/ExportService.hpp"
#include "../Servers/ImportService.hpp"
#include "../Servers/OrderService.hpp"



namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWidget(QWidget *parent = nullptr);
    ~ReportWidget();

public slots:
    void globalUpdate();


private:
    Ui::ReportWidget *ui;
};

#endif // REPORTWIDGET_HPP
