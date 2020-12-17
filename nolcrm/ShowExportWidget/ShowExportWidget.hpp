#ifndef NOLCRM_SHOWEXPORTWIDGET_HPP
#define NOLCRM_SHOWEXPORTWIDGET_HPP


#include <QWidget>
#include <DataBase/Service.hpp>

namespace Ui {
class ShowExportWidget;
}

class ShowExportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShowExportWidget(QWidget *parent = nullptr);
    ~ShowExportWidget();

public slots:
    void globalUpdate();

private slots:
    void on_tableWidget_activated(const QModelIndex &index);

private:
    Ui::ShowExportWidget *ui;
};

#endif
