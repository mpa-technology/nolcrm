#pragma once
#include <QWidget>
#include <QFileDialog>
#include <MainWindow/MainWindow.hpp>
#include <Settings/Settings.hpp>


namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LoginWidget *ui;
};


