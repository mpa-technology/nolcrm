/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#ifndef NOLCRM_SETTINGS_HPP
#define NOLCRM_SETTINGS_HPP

#include <QSettings>
#include <QDebug>


class Settings{


    Settings();
    Settings(const Settings& root) = delete;
    Settings& operator=(const Settings&) = delete;


    QSettings* settings_ = nullptr;


public:

    ~Settings();

    static Settings& self();


    static void setValue( const QString& key, const QVariant& value);

    static QVariant value( const QString& key, const QVariant& defaultValue);


    static bool mainSettingsLoad(){
        QString dbName = Settings::self().value("database/name","@NULL").toString();
        return dbName != "@NULL";
    }

};

#endif
