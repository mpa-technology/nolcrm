/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_IMPORTSERVICE_HPP
#define NOL_CRM_IMPORTSERVICE_HPP

#include "GlobalEmitService.hpp"
#include "../DataBase/TableStorageImport.hpp"
#include "../DataBase/TableStorage.hpp"

class ImportService : public QObject{
    Q_OBJECT

    ImportService();
    ImportService(const ImportService& root) = delete;
    ImportService& operator=(const ImportService&) = delete;


    struct {
        bool isCache = false;
        QVector<ImportStorage> list;
    }allImportCache_;

public:

    static ImportService& self();

    static  bool newImport ( const ImportStorage& is);

    static QVector<ImportStorage> getAllImport();





public slots:
    void gloablCacheClear();

};



#endif // NOL_CRM_IMPORTSERVICE_HPP
