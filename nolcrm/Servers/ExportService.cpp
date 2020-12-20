/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "ExportService.hpp"


ExportService::ExportService(){
    allExportCache_.isCache = false;
    QObject::connect(&GlobalEmitService::self(),SIGNAL(gloablCacheClear()),this,SLOT(gloablCacheClear()));

}

ExportService &ExportService::self(){
    static ExportService sig;
    return sig;
}

bool ExportService::newExport(const ExportStorage &is){


    if(!TableStorageExport::newExport(is)){
        return false;
    }

    for(auto it2 : is.products){
        if(!TableStorage::subCount(it2.id,it2.count))
            return false;
    }

    self().allExportCache_.isCache = false;
    self().allExportCache_.list.clear();

    return true;
}

QVector<ExportStorage> ExportService::getAllExport(){

    auto& ae = self().allExportCache_;

    if(ae.isCache)
        return ae.list;

    ae.list = TableStorageExport::getAllExport();
    ae.isCache = true;

    return ae.list;
}

ExportStorage ExportService::getExport(const quint64 &code)
{
    auto& ae = self().allExportCache_;
    if(ae.isCache){
        for(const auto& it : ae.list)
            if(it.code == code)
                return it;
    }else{
        ae.list = getAllExport();
        ae.isCache = true;
        for(const auto& it : ae.list)
            if(it.code == code)
                return it;
    }




    return {};
}




void ExportService::gloablCacheClear()
{
    allExportCache_.isCache = false;
    allExportCache_.list.clear();
}
