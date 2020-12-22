/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_UPDATESERVICE_HPP
#define NOL_CRM_UPDATESERVICE_HPP

#include <QObject>
#include <QDebug>

class GlobalEmitService : public QObject{
    Q_OBJECT

public:

    static GlobalEmitService& self();

public slots:

    static void emitGlobalUpdate();
    static void emitGloablCacheClear();


signals:
    void globalUpdate();
    void gloablCacheClear();



};



#endif //NOL_CRM_UPDATESERVICE_HPP
