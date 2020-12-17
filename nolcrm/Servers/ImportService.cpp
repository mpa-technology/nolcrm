/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "ImportService.hpp"



ImportService::ImportService(){}

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


    return true;
}
