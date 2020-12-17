#ifndef NOLCRM_WIDGETNEWEXPORT_HPP
#define NOLCRM_WIDGETNEWEXPORT_HPP




#include <QWidget>
#include <QMessageBox>
#include <DataBase/TableProducts.hpp>
#include <DataBase/TableStorageImport.hpp>
#include <DataBase/Service.hpp>

namespace Ui {
class WidgetNewExport;
}

class WidgetNewExport : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNewExport(QWidget *parent = nullptr);
    ~WidgetNewExport();

public slots:
    void globalUpdate();



private slots:
    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::WidgetNewExport *ui;
};

#endif
