/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_GLOBALSERVICE_HPP
#define NOL_CRM_GLOBALSERVICE_HPP

#include <QDebug>

#include "../DataBase/DataBase.hpp"
#include "../DataBase/TableOrders.hpp"
#include "../DataBase/TableProducts.hpp"


#include "../DataBase/TableStorage.hpp"
#include "../DataBase/TableStorageImport.hpp"
#include "../DataBase/TableStorageExport.hpp"

class GlobalService{

    GlobalService();
    GlobalService(const GlobalService& root) = delete;
    GlobalService& operator=(const GlobalService&) = delete;

    bool initDataBase_();


public:

    ~GlobalService();

    static GlobalService& self();


    static  bool waekup();


    void initTableBase();



};



#endif // NOL_CRM_GLOBALSERVICE_HPP
