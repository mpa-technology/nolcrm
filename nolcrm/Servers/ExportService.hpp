/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_EXPORTSERVICE_HPP
#define NOL_CRM_EXPORTSERVICE_HPP
#include <DataBase/TableStorage.hpp>
#include <DataBase/TableStorageExport.hpp>

class ExportService{
    ExportService();
    ExportService(const ExportService& root) = delete;
    ExportService& operator=(const ExportService&) = delete;

    struct {
        bool isCache = false;
        QVector<ExportStorage>list;
    }allExport_;


public:

    static ExportService& self();

    static  bool newExport( const ExportStorage& is);

    static QVector<ExportStorage> getAllExport();
    
    static ExportStorage getExport(const quint64& code);

};

#endif // NOL_CRM_EXPORTSERVICE_HPP
