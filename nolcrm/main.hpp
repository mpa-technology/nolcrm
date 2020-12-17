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

#include <LoginWidget/LoginWidget.hpp>
#include "DataBase/DataBase.hpp"
#include "DataBase/TableStorage.hpp"
#include "Settings/Settings.hpp"
#include "MainWindow/MainWindow.hpp"
#include "Servers/ProgramService.hpp"
#include "Servers/UpdateService.hpp"
#include "Servers/GlobalService.hpp"

struct logFile{

    FILE* file = nullptr;

    logFile();

    ~logFile();

};


void MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);




int main(int argc, char *argv[]);



#endif