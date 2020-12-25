/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "GlobalEmitService.hpp"


GlobalEmitService &GlobalEmitService::self(){
    static GlobalEmitService sig;
    return sig;
}

void GlobalEmitService::emitGlobalUpdate(){
    qDebug()<<"emit globalUpdate";
    emit self().globalUpdate();
}

void GlobalEmitService::emitGloablCacheClear(){
    qDebug()<<"emit gloablCacheClear";
    emit self().gloablCacheClear();
}
