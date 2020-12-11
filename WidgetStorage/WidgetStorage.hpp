#pragma once
#include <QWidget>
#include <DataBase/Service.hpp>


namespace Ui {
class WidgetStorage;
}

class WidgetStorage : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetStorage(QWidget *parent = nullptr);
    ~WidgetStorage();

private:
    Ui::WidgetStorage *ui;
};


