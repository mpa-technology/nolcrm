/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "UpdateService.hpp"


UpdateService &UpdateService::self(){
    static UpdateService sig;
    return sig;
}

void UpdateService::emitGlobalUpdate(){
    qDebug()<<"emit globalUpdate";
    emit globalUpdate();
}
