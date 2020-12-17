#ifndef NOLCRM_TABLESTORAGE_HPP
#define NOLCRM_TABLESTORAGE_HPP

#include "DataBase.hpp"

struct Storage{
quint64 pid;
quint64 count;
};


class TableStorage{


    TableStorage();
    TableStorage(const TableStorage& root) = delete;
    TableStorage& operator=(const TableStorage&) = delete;


    bool tableCreate_ = false;
    QSqlError lastError_;

public:

    static TableStorage& self();

    static QSqlError lastError();

    static bool crateTable();

    static QSqlError addItem(const quint64& id);

    static bool setCount(const quint64& id,const quint64& count);
    static bool addCount(const quint64& id,const quint64& count);
    static bool subCount(const quint64& id,const quint64& count);
    static quint64 getCount(const quint64& id);


    //TODO: rename
    static Storage getItem(const quint64& id);



    //TODO: not test
    static bool itemExist(const quint64& id);

};


#endif
