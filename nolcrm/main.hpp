/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/


#ifndef NOLCRM_CRM_MAIN_HPP
#define NOLCRM_CRM_MAIN_HPP

#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QtGlobal>
#include <QFile>
#include <QScopedPointer>
#include <QSharedPointer>

#include "LoginWidget/LoginWidget.hpp"
#include "DataBase/DataBase.hpp"
#include "DataBase/TableStorage.hpp"
#include "Settings/Settings.hpp"
#include "MainWindow/MainWindow.hpp"
#include "Servers/ProgramService.hpp"
#include "Servers/GlobalEmitService.hpp"
#include "Servers/GlobalService.hpp"

class App{


    QApplication* qApplication_ = nullptr;



    static void MessageOutput_(QtMsgType type, const QMessageLogContext &context, const QString &msg);



public:

    App(int argc, char** argv);

    ~App();


    int run();


};




int main(int argc, char *argv[]);



#endif
