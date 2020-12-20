/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "ImportService.hpp"



ImportService::ImportService(){

    QObject::connect(&GlobalEmitService::self(),SIGNAL(gloablCacheClear()),this,SLOT(gloablCacheClear()));
    allImportCache_.isCache = false;
}

ImportService &ImportService::self(){
    static ImportService sig;
    return sig;
}

bool ImportService::newImport(const ImportStorage &is){

    if(!TableStorageImport::newImport(is)){
        return false;
    }

    for(auto it2 : is.products){
        if(!TableStorage::addCount(it2.id,it2.count))
            return false;
    }


    self().allImportCache_.list.clear();
    self().allImportCache_.isCache = false;

    return true;
}

QVector<ImportStorage> ImportService::getAllImport(){
    auto& th = self();


    if(th.allImportCache_.isCache)
        return th.allImportCache_.list;

    th.allImportCache_.list =  TableStorageImport::getAllImport();
    th.allImportCache_.isCache = true;

    return th.allImportCache_.list;
}

void ImportService::gloablCacheClear(){
    allImportCache_.isCache = false;
    allImportCache_.list.clear();
}
