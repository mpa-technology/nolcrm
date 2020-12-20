/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef NOL_CRM_GLOBALSERVICE_HPP
#define NOL_CRM_GLOBALSERVICE_HPP

#include <QDebug>
#include <QTimer>



class GlobalService{

    GlobalService();
    GlobalService(const GlobalService& root) = delete;
    GlobalService& operator=(const GlobalService&) = delete;

    bool initDataBase_();


    struct{
    QTimer* cache;
    }Timers_;




public:

    ~GlobalService();

    static GlobalService& self();

    static  bool waekup();

    void initTableBase();


    static size_t cacheSize();


};



#endif // NOL_CRM_GLOBALSERVICE_HPP
