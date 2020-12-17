/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "ProgramService.hpp"

ProgramService::ProgramService()
{

}


ProgramService::BUILD_TYPE ProgramService::buildType(){
    QString type = NOLCRM_BUILD_TYPE;

    return type == "Release" ? RELEASE:DEBUG;
}

QString ProgramService::buildTypeString(){
    QString type = NOLCRM_BUILD_TYPE;

    return buildType() == RELEASE ? "Release":"Debug";
}

QString ProgramService::version(){
    return "1.2.0";
}

QString ProgramService::name(){
    return "nolcrm";
}
