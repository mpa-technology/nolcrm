/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_EXPORTSERVICE_HPP
#define NOL_CRM_EXPORTSERVICE_HPP

#include "GlobalEmitService.hpp"
#include "../DataBase/TableStorage.hpp"
#include "../DataBase/TableStorageExport.hpp"

class ExportService: public QObject{
    Q_OBJECT

    ExportService();
    ExportService(const ExportService& root) = delete;
    ExportService& operator=(const ExportService&) = delete;

    struct {
        bool isCache = false;
        QVector<ExportStorage>list;
    }allExportCache_;


public:

    static ExportService& self();

    static  bool newExport( const ExportStorage& is);

    static QVector<ExportStorage> getAllExport();
    
    static ExportStorage getExport(const quint64& code);

    static size_t cacheSize(){
        return self().allExportCache_.list.size() * sizeof (ExportStorage);
    }


public slots:
    void gloablCacheClear();


};

#endif // NOL_CRM_EXPORTSERVICE_HPP
