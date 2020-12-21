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

void ExportService::newExport(const ExportStorage &is){


    TableStorageExport::newExport(is);


    for(auto it2 : is.products)
        TableStorage::subCount(it2.id,it2.count);


    self().allExportCache_.isCache = false;
    self().allExportCache_.list.clear();


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

size_t ExportService::cacheSize(){
    return self().allExportCache_.list.size() * sizeof (ExportStorage);
}




void ExportService::gloablCacheClear()
{
    allExportCache_.isCache = false;
    allExportCache_.list.clear();
}
