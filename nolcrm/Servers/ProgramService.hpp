/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#ifndef CRM_NOL_PROGRAMSERVICE_HPP
#define CRM_NOL_PROGRAMSERVICE_HPP

#include <QString>
#include <Servers/cmake_m.hpp>

class ProgramService{

    ProgramService();


public:
    enum BUILD_TYPE{
        RELEASE,
        DEBUG
    };

    static BUILD_TYPE buildType();


    static QString buildTypeString();



    static QString version();

    static QString name();

};


#endif // CRM_NOL_PROGRAMSERVICE_HPP
