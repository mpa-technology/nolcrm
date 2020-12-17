/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_IMPORTSERVICE_HPP
#define NOL_CRM_IMPORTSERVICE_HPP


#include <DataBase/TableStorageImport.hpp>
#include <DataBase/TableStorage.hpp>

class ImportService{
    ImportService();
    ImportService(const ImportService& root) = delete;
    ImportService& operator=(const ImportService&) = delete;

public:

    static ImportService& self();

    static  bool newImport ( const ImportStorage& is);


};



#endif // NOL_CRM_IMPORTSERVICE_HPP
