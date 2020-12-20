/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_UPDATESERVICE_HPP
#define NOL_CRM_UPDATESERVICE_HPP

#include <QObject>
#include <QDebug>

class UpdateService : public QObject{
    Q_OBJECT

public:

    static UpdateService& self();

public slots:

    void emitGlobalUpdate();
    void emitGloablCacheClear();


signals:
    void globalUpdate();
    void gloablCacheClear();



};



#endif
