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


public slots:
void globalUpdate();

private:
    Ui::WidgetStorage *ui;
};


