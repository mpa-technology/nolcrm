#ifndef NOLCRM_SHOWIMPORTWIDGET_HPP
#define NOLCRM_SHOWIMPORTWIDGET_HPP



#include <QWidget>
#include <DataBase/Service.hpp>


namespace Ui {
class ShowImportWidget;
}

class ShowImportWidget : public QWidget
{
    Q_OBJECT




public:
    explicit ShowImportWidget(QWidget *parent = nullptr);
    ~ShowImportWidget();


public slots:
void globalUpdate();

private slots:
void on_tableWidget_activated(const QModelIndex &index);

private:
    Ui::ShowImportWidget *ui;
};

#endif
