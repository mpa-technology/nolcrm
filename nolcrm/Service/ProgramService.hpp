/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#pragma once

#include <QString>
#include "cmake_m.hpp"

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


